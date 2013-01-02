require 'template/template'

local ModuleName = 'template'
local Template = {}

local gameVersions = { 'Game version DOS', 'Game version Amiga' }

local MenuCommands = { ["Change palette"] = ChangePalette }


UTTModules[ModuleName] = Template



function Template.selectVersion()
	local res = selectVersionDialog( gameVersions )
	res = findStringInTable( gameVersions, res )
	if res ~= nil then
		currentVersion = res
		setModuleReady()
	end
end



function Template.setVersion( version )
	local res = findStringInTable( gameVersions, version )
	if res ~= nil then
		currentVersion = res
		return true
	end
end



function Template.getVersions()
	return gameVersions
end



function Template.getModuleName()
	return gameVersions[currentVersion]
end



function Template.getModuleMenu()
	local menuItems = {}
	
	for command, func in pairs( MenuCommands ) do
		table.insert(menuItems, command)
	end
	
	return menuItems
end



function Template.ImportFont()
	local fileName = openFileDialog("Font file (FONT.FNT)|font.fnt|Font file (*.FNT)|*.fnt")
	
	if fileName ~= nil then
		local font = LoadTemplateFont( fileName )
		if font ~= nil then
			editFont(font)
		end
	end
end



function Template.ImportImage()
	local fileName = openFileDialog("Image Files (*.IMG)|*.img")
	
	if fileName ~= nil then
		local image = LoadTemplateImage( fileName )
		
		if image then
			editImage(image)
		end
	end
end



function Template.ImportLibrary()
	local fileName = openFileDialog("WAD Files (*.WAD)|*.wad")
	
	if fileName ~= nil then
		local lib = LoadTemplateLibrary( fileName )
		
		if lib then
			editLibrary(lib)
		end
	end
end




function Template.executeModuleMenuCommand( command, editorId )
	MenuCommands[command](Template.GamePath, editorId)
end




print "Template module can't be loaded!!!"
