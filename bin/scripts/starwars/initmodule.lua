require 'starwars/tie'

local ModuleName = 'starwars'
local Starwars = {}

local gameVersions = { "X-Wing-95", "TIE Fighter-95" }

local MenuCommands = { ["Change palette"] = ChangePalette }


UTTModules[ModuleName] = Starwars



function Starwars.selectVersion()
	local res = selectVersionDialog( gameVersions )
	res = findStringInTable( gameVersions, res )
	if res ~= nil then
		currentVersion = res
		setModuleReady()
	end
end



function Starwars.setVersion( version )
	local res = findStringInTable( gameVersions, version )
	if res ~= nil then
		currentVersion = res
		return true
	end
end



function Starwars.getVersions()
	return gameVersions
end



function Starwars.getModuleName()
	return gameVersions[currentVersion]
end



function Starwars.getModuleMenu()
	local menuItems = {}
	
	for command, func in pairs( MenuCommands ) do
		table.insert(menuItems, command)
	end
	
	return menuItems
end



function Starwars.ImportFont(fileName)
	if not fileName then
		fileName = openFileDialog("Font file (*.FNT)|*.fnt")
	end
	
	if fileName then
		local font = LoadStarwarsFont( fileName )
		if font ~= nil then
			editFont(font)
		end
	end
end



function Starwars.ImportImage(fileName)
	if not fileName then
		fileName = openFileDialog("Image Files (*.IMG)|*.img")
	end	
	
	if fileName then
		local image = LoadStarwarsImage( fileName )
		
		if image then
			editImage(image)
		end
	end
end



function Starwars.ImportLibrary(fileName)
	if not fileName then
		fileName = openFileDialog("LFD Files (*.LFD)|*.lfd")
	end
	
	if fileName then
		local lib = LoadLFD( fileName )
		
		if lib then
			editLibrary(lib)
		end
	end
end




function Starwars.executeModuleMenuCommand( command, editorId )
	MenuCommands[command](Starwars.GamePath, editorId)
end



function Starwars.libExtractFolders(lib, items)
	local root = lib:GetRoot()
	local origin = lib:GetOrigin()
	
	for i = 1, #items do
	
		if items[i] == root then
			UnpackFullLFD(lib)
		end
	end
end



function Starwars.libReplaceFolder(lib, items)
end

function Starwars.libExtractFiles(lib, items)
end

function Starwars.libReplaceFiles(lib, items)
end

function Starwars.libItemRuntimeEdit(lib, items)
end


print "Starwars module loaded"
