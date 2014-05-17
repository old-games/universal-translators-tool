require 'xcom/xcom'

local ModuleName = 'xcom'
local Xcom = {}

local gameVersions = { 'UFO 1 (DOS)', 'UFO 2 (WIN)' }

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



function Xcom.setVersion( version )
	local res = findStringInTable( gameVersions, version )
	if res ~= nil then
		currentVersion = res
		return true
	end
end



function Xcom.getVersions()
	return gameVersions
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



function Xcom.ImportFont(filename)
	if not filename then
		filename = openFileDialog("Font file (BIGLETS.DAT)|biglets.dat|Font file (SMALLSET.DAT)|smallset.dat")
	end

	if filename ~= nil then
		local font = LoadXcomFont( filename )
		
		if font ~= nil then
			editFont(font)
		end
	end
end




local function imageTypeSelector(filename)
	local path, name, ext = parseFileName( filename:lower() )
	path = path..'/'

	if ext == "lbm" then
		return LoadLBM( filename )
	elseif ext == "scr" or ext == "dat" then
		return LoadXcomImage( filename )
	end
	
end




function Xcom.ImportImage(filename)
	if not filename then
		filename = openFileDialog("LBM Files (*.LBM)|*.lbm|Background files (*.SCR)|*.scr|DAT files (*.DAT)|*.dat")
	end
	
	if filename ~= nil then
		local image = imageTypeSelector( filename )
		
		if image then
			editImage(image)
		end
	end
end




local CATStruct = {}
CATStruct[1] =	{ OFFSET	= "DWORD" 	}
CATStruct[2] =	{ SIZE 		= "DWORD" 	}



function loadCAT( filename )
	local path, name, ext = parseFileName( filename )
	local origin = Origin.new(filename)
	
	if ext == "lbm" then
		local iff = IFFLib.new()
		iff:LoadIFFFile( filename )
		iff:SetOrigin( origin )
		return iff
	end
	
	local fh = assert(io.open(filename, "rb"))
	if not fh then
		return
	end
	
	local done = false
	local size = fileSize( filename )
	local items = {}

	while not done do
		local data = readData( fh, CATStruct )
		
		if not data then
			break
		end
		
		table.insert(items, data)
		done = fh:seek() >= items[1].OFFSET
	end
	fh:close()

	if not done then 
		return
	end
	
	local lib = LibTree.new()
	local root = lib:GetRoot()
	for i, current in ipairs(items) do
		local item = lib:AddItem( root )
		local data = LibItemData.new()
		data.mLibDataOffset = current.OFFSET
		item:SetText( name.." #"..tostring(i) )
		item:SetData( data )
	end
	
	
	lib:SetOrigin( origin )
	
	return lib
end




function Xcom.ImportLibrary(filename)
	if not filename then
		fileName = openFileDialog("CAT Files (*.CAT)|*.cat|LBM Files (*.LBM)|*.lbm")
	end
	
	if filename ~= nil then
		local lib = loadCAT( filename )
		
		if lib then
			editLibrary(lib)
		end
	end
end



function Xcom.ImportVideo(filename)
	if not filename then
		filename = openFileDialog("VID Files (*.VID)|*.vid")
	end
	
	if filename ~= nil then
		local video = LoadXComVID( filename )
		
		if video then
			editVideo(video)
		end
	end
end




function Xcom.executeModuleMenuCommand( command, editorId )
	MenuCommands[command](Xcom.GamePath, editorId)
end




print 'Xcom module loaded'
