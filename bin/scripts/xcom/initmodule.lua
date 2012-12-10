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



function Operations.loadLBM( filename )
	iff = IFFLib:new()
	iff:LoadIFFFile( filename )
end


function Xcom.executeModuleMenuCommand( command )
	MenuCommands[command]()
end




print 'Xcom module loaded'
