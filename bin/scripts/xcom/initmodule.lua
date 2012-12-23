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



function Xcom.ImportFont()
	local fileName = openFileDialog("Font file (BIGLETS.DAT)|biglets.dat|Font file (SMALLSET.DAT)|smallset.dat")
	
	if fileName ~= nil then
		local font = LoadXcomFont( fileName )
		if font ~= nil then
			editFont(font)
		end
	end
end




local function imageTypeSelector( filename )
	local path, name, ext = parseFileName( filename:lower() )
	path = path..'/'

	if ext == "lbm" then
		return LoadLBM( filename )
	elseif ext == "scr" then
	
	elseif ext == "dat" then
	
	end
	
end




function Xcom.ImportImage()
	local fileName = openFileDialog("LBM Files (*LBM.DAT)|*.lbm|Background files (*.SCR)|*.scr|DAT files (*.DAT)|*.dat")
	
	if fileName ~= nil then
		local image = imageTypeSelector( fileName )
		
		if image then
			editImage(image)
		end
	end
end





--	local fh = assert(io.open(filename, "rb"))
--	if not fh then
--		return
--	end
--	
--	 
--	if name == 'biglets' or name == 'smallset' then
--		LoadXcomFont( path, name, fh )
--	else
--		local key = findAnyStringInTable( getKnownImageNames(), name )
--		if key ~= nil then
--			LoadXcomImage( path, name, key, fh )
--		else
--			print ("I don't know what to do with ", filename)
--		end
--	end
--	fh:close()
--end



local CATStruct = {}
CATStruct[1] =	{ OFFSET	= "DWORD" 	}
CATStruct[2] =	{ SIZE 		= "DWORD" 	}



--function Operations.loadCAT( filename )
--	local vol, path, name, ext = parseFileName( filename )
--	path = vol..path..'/'
--
--	local fh = assert(io.open(filename, "rb"))
--	if not fh then
--		return
--	end
--	
--	local done = false
--	local size = fileSize( filename )
--	
--	while not done do
--		local data = readData( fh, CATStruct )
--		done = (data ~= nil) and (data.OFFSET + data.SIZE) == size
--		showTable(data)
--	end
--	
--	fh:close()
--end







function Xcom.executeModuleMenuCommand( command, editorId )
	MenuCommands[command](Xcom.GamePath, editorId)
end




print 'Xcom module loaded'
