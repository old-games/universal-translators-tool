require 'xcom/xcom'

local ModuleName = 'xcom'
local Xcom = {}

local gameVersions = { 'UFO 1 (DOS)', 'UFO 2 (WIN)' }

local ActionsOnExtension = 
{ 
	dat = "loadDAT",
	scr = "loadDAT",
	cat = "loadCAT",
	lbm = "loadLBM"
}



local Operations = {}

local MenuCommands = { ["Change palette"] = ChangePalette }


UTTModules[ModuleName] = Xcom



function Xcom.selectVersion()
	local res = selectVersionDialog( gameVersions )
	res = findStringInTable( gameVersions, res )
	if res ~= nil then
		currentVersion = res
		setModuleReady()
	end
end



function Xcom.getModuleName()
	return gameVersions[currentVersion]
end



function Xcom.getModuleMenu()
	local menuItems = {}
	
	for command, func in pairs( MenuCommands ) do
		table.insert(menuItems, command)
	end
	
	return menuItems
end



function Xcom.getExtensions()
	return '*.DAT (*.dat)|*.dat|*.SCR (*.scr)|*.scr|*.CAT (*.cat)|*.cat|*.LBM (*.lbm)|*.lbm'
end



function Xcom.ImportFont()
	local fileName = openFileDialog("Font file (BIGLETS.DAT)|biglets.dat|Font file (SMALLSET.DAT)|smallset.dat")
	
	if fileName ~= nil then
		Operations.loadDAT( fileName )
	end
end


function Xcom.openFile( fileName )
	local fileName = string.lower( fileName )
	local vol, path, name, ext = parseFileName( fileName )
	local key = ActionsOnExtension[ ext ]
	if key == nil then
		print( "Can't find function for '"..ext.."' extension" )
		return
	end
	Operations[ key ]( fileName )
end



function Operations.loadDAT( filename )
	--local busy = BusyCursor:new()
	
	local vol, path, name, ext = parseFileName( filename )
	path = vol..path..'/'

	local fh = assert(io.open(filename, "rb"))
	if not fh then
		return
	end
	
	 
	if name == 'biglets' or name == 'smallset' then
		LoadXcomFont( path, name, fh )
	else
		local key = findAnyStringInTable( getKnownImageNames(), name )
		if key ~= nil then
			LoadXcomImage( path, name, key, fh )
		else
			print ("I don't know what to do with ", filename)
		end
	end
	fh:close()
end



local CATStruct = {}
CATStruct[1] =	{ OFFSET	= "DWORD" 	}
CATStruct[2] =	{ SIZE 		= "DWORD" 	}



function Operations.loadCAT( filename )
	local vol, path, name, ext = parseFileName( filename )
	path = vol..path..'/'

	local fh = assert(io.open(filename, "rb"))
	if not fh then
		return
	end
	
	local done = false
	local size = fileSize( filename )
	
	while not done do
		local data = readData( fh, CATStruct )
		done = (data ~= nil) and (data.OFFSET + data.SIZE) == size
		showTable(data)
	end
	
	fh:close()
end


--1      2        Height         Image height (Big endian)
--2      2        Width          Image width (Big endian)
--3      2        x-orig         Where on screen, in pixels, the image's top-left corner is. Value is
--4      2        y-orig         usually 0,0 unless image is part of a larger image or not fullscreen.
--5      1        Planes         Number of planes in bitmap, 1 for monochrome, 4 for 16 color, 8 for 256 color
--                               If 0 we have a colormap
--6      1        Mask           1 = masked, 2 = transparent color, 3 = lasso (For MacPaint) Mask data is not
--                               considered a bit plane
--7      2        Compression    If 1 then image data is RLE compressed
--8      2        Trans color    Transparent color, useful only for Mask > 1
--9      1        xAspect        Pixel aspect, a ratio width:height; used for displaying the image
--10     1        yAspect        on a variety of different screen resolutions for 320x200 5:6 or 10:11
--11     2        PageWidth      The size of the screen the image is to be displayed on, in pixels,
--12     2        PageHeight     Usually 320x200

LBMHeader = {}
LBMHeader[1] = { WIDTH 			= "WORD_BE"	}
LBMHeader[2] = { HEIGHT			= "WORD_BE"	}
LBMHeader[3] = { X 				= "WORD_BE"	}
LBMHeader[4] = { Y 				= "WORD_BE"	}
LBMHeader[5] = { BPP			= "BYTE" 	}
LBMHeader[6] = { MASK 			= "BYTE" 	}
LBMHeader[7] = { COMPRESSION	= "WORD" 	}
LBMHeader[8] = { TRANSPARENT	= "WORD_BE"	}
LBMHeader[9] = { XASPECT		= "BYTE" 	}
LBMHeader[10] = { YASPECT		= "BYTE" 	}
LBMHeader[11] = { PAGEWIDTH		= "WORD_BE"	}
LBMHeader[12] = { PAGEHEIGHT 	= "WORD_BE"	}



function Operations.loadLBM( filename )
	iff = IFFLib:new()
	iff:LoadIFFFile( filename )
	
	local form = iff:FindForm("PBM ")
	
	if not form:IsOk() then
		print("PBM form not found!")
		return
	end
	
	local header = iff:FindChunk("BMHD", form)
	local colorMap = iff:FindChunk("CMAP", form)
	local body = iff:FindChunk("BODY", form)
	
	if not header:IsOk()  then
		print "BMHD not loaded!"
		return
	end
	
	if not colorMap:IsOk()  then
		print "CMAP not loaded!"
		return
	end
	
	if not body:IsOk()  then
		print "BODY not loaded!"
		return
	end
		
	local info = readDataFromBuffer( iff:ReadChunkData(header), LBMHeader )
	
	showTable(info)
	
	
	local palBuf = iff:ReadChunkData(colorMap)
	local imgBuf = iff:ReadChunkData(body)
	
	
	
	local size = info.WIDTH * info.HEIGHT
	local image = ImageInfo:new()
	local pal = Palette:new()
	
	if pal:Initiate( Palette.bpp8, palBuf, Palette.sfPlain, false ) then
		if not image:SetPalette( pal ) then
			print "loadLBM error: can't set Palette."
			return
		end
	end
		
	local mask = IndexMask:new()
	mask:SetMask( unpackLBMBody(imgBuf, size), size, info.WIDTH, info.HEIGHT, -1, -1)
	if mask:IsOk() then
		image:SetImage( mask )
		editImage( image )
	else
		print("loadLBM error: There was an error while initiating IndexMask")
	end
	
end


function Xcom.executeModuleMenuCommand( command )
	MenuCommands[command]()
end




print 'Xcom module loaded'
