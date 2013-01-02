require 'starwars/tie'

local ModuleName = 'starwars'
local Starwars = {}

local gameVersions = { "X-Wing'95", "TIE Fighter'95" }

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



function Starwars.ImportFont()
	local fileName = openFileDialog("Font file (*.FNT)|*.fnt")
	
	if fileName ~= nil then
		local font = LoadStarwarsFont( fileName )
		if font ~= nil then
			editFont(font)
		end
	end
end



function Starwars.ImportImage()
	local fileName = openFileDialog("Image Files (*.IMG)|*.img")
	
	if fileName ~= nil then
		local image = LoadStarwarsImage( fileName )
		
		if image then
			editImage(image)
		end
	end
end



function Starwars.ImportLibrary()
	local fileName = openFileDialog("LFD Files (*.LFD)|*.lfd")
	
	if fileName ~= nil then
		local lib = LoadLFD( fileName )
		
		if lib then
			editLibrary(lib)
		end
	end
end




function Starwars.executeModuleMenuCommand( command, editorId )
	MenuCommands[command](Starwars.GamePath, editorId)
end




print "Starwars module loaded"
