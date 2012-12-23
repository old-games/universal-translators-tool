print "Starting Lua initiate..."

package.path = package.path..";./scripts/?.lua"
require 'common'
require 'structs'



-- list of module names, there are no auto searching new module in UTT
-- new module must be added to this list
ModuleFolders = { 'example', 'privateer2', 'xcom', 'frontier' }



-- table with references to modules
UTTModules = {}


-- initiates all modules that are defined in ModuleFolders
function initModules()
	for i = 1, #ModuleFolders do
		local fileName = ModuleFolders[i]..'/initmodule'
		require( fileName )
	end
end



initModules()

CurrentModule = nil -- UTTModules['xcom']	-- set it to nil for module selection on program start


-- returns current active module
function getCurrentModule()
	return CurrentModule
end


-- runs command from special section of Main Menu - Module 
function executeModuleMenuCommand( command, id )
	if CurrentModule ~= nil then
		return CurrentModule.executeModuleMenuCommand( command, id )
	end
end


-- returns names of current module
function getModuleName()
	if CurrentModule ~= nil then
		return CurrentModule.getModuleName()
	end
end


-- returns commands to fill Module menu
function getModuleMenu()
	if CurrentModule ~= nil and CurrentModule.getModuleMenu ~= nil then
		return CurrentModule.getModuleMenu()
	end
end



function getModuleVersions(moduleName)
	return UTTModules[ moduleName ].getVersions()
end



function getAvailableModules()
	local result = {}
	
	for key, value in pairs(UTTModules) do
		if value ~= nil then
			table.insert(result, key)
		end
	end
	
	return result
end



function hasModuleCommand( command )
	return CurrentModule ~= nil and CurrentModule[command] ~= nil
end



function doModuleCommand( command )
	CurrentModule[command]()
end



-- returns list of files extensions that are allowed to open
function getExtensions()
	if CurrentModule ~= nil then
		return CurrentModule.getExtensions()
	end
end


-- command Open from main menu 
function openFile( fileName )
	if CurrentModule ~= nil then
		return CurrentModule.openFile( fileName )
	end
end


-- command Select Version from main menu
function selectVersion( fileName )
	if CurrentModule ~= nil then
		if CurrentModule.selectVersion == nil then
			print("There no other versions for currently selected module")
		else 
			return CurrentModule.selectVersion()
		end
	end
end



-- command Select Module from main menu
function selectModule()
	-- we will allow user to select only succesfully loaded module
	local loadedModules = {}
	for k in pairs(UTTModules) do
		table.insert( loadedModules, k )
	end
	table.sort( loadedModules )
	
	local name = selectModuleDialog( loadedModules )
	if not name or string.len(name) == 0 then
		return
	end
	
	print (name..' module selected.')
	CurrentModule = UTTModules[ name ]
	setModuleReady()
end



function setCurrentModule( moduleName, gamePath )
	print ("setCurrentModule: ", moduleName)
	
	CurrentModule = UTTModules[ moduleName ]
	CurrentModule["GamePath"] = gamePath
	
	setModuleReady()
end



function setModuleVersion( versionName )
	print ("setModuleVersion: ", versionName)
	if CurrentModule ~= nil and CurrentModule.setVersion ~= nil then
		if CurrentModule.setVersion( versionName ) then 
			setModuleReady()
		end
	end
end



-- set current module to any correct value to avoid module selection dialog on start/restart
--if CurrentModule == nil then
--	selectModule()
--else
--	setModuleReady()
--end



print "Scripts initiated. Press '~' to show Lua console. Call reboot() to restart scripts."