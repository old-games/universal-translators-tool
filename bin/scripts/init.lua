--[[!
	\file 
	\brief Модуль инициации скриптов UTT
	]]

print "Starting Lua initiate..."

package.path = package.path..";./scripts/?.lua"
require 'common'
require 'structs'



-- list of module names, there are no auto searching new module in UTT
-- new module must be added to this list
--! \brief Список имён модулей, в UTT нет автопоиска новых модулей, новые модули должны быть вручную вписаны в этот массив.
--! Имя модуля должно соответствовать названию каталога в котором располагается модуль.
ModuleFolders = { 'example', 'privateer2', 'xcom', 'frontier', 'starwars' }



-- table with references to modules
--! \brief Массив модулей, каждый модуль при загрузке должен сам прописать себя в этот массив
UTTModules = {}


-- initiates all modules that are defined in ModuleFolders
--! \brief Функция инициализации модулей
function initModules()
	for i = 1, #ModuleFolders do
		local fileName = ModuleFolders[i]..'/initmodule'
		require( fileName )
	end
end



initModules()

--! \brief Переменая в которой хранится ссылка на текущий активный модуль.
CurrentModule = nil


--! \brief функция возвращает текущий модуль
--! \return table - таблица функций игры
function getCurrentModule()
	return CurrentModule
end


-- runs command from special section of Main Menu - Module
--! \brief Запрашивает выполнение функции связанной с командой меню модуля
--! Меню модуля создаётся при инициализации модуля (см. примеры).
--! \return пока не определено 
function executeModuleMenuCommand( command, id )
	if CurrentModule ~= nil then
		return CurrentModule.executeModuleMenuCommand( command, id )
	end
end


-- returns names of current module
--! \brief Возвращает название текущего модуля.
--! Это может быть более подробное описание модуля, чем просто имя модуля.
--! \return string
function getModuleName()
	if CurrentModule ~= nil then
		return CurrentModule.getModuleName()
	end
end


-- returns commands to fill Module menu
--! \brief Возвращает список доступных команд для меню модуля.
--! \return table - массив строк
function getModuleMenu()
	if CurrentModule ~= nil and CurrentModule.getModuleMenu ~= nil then
		return CurrentModule.getModuleMenu()
	end
end


--! \brief Возвращает список версий модуля.
--! Или ничего, если версия только одна.
--! \param string - имя модуля
--! \return table - массив строк
function getModuleVersions(moduleName)
	if UTTModules[ moduleName ] and UTTModules[ moduleName ].getVersions then
		return UTTModules[ moduleName ].getVersions()
	end
end



--! \brief Возвращает список доступных модулей
--! \return table - массив строк
function getAvailableModules()
	local result = {}

	for key, value in pairs(UTTModules) do
		if value ~= nil then
			table.insert(result, key)
		end
	end

	return result
end



--! \brief Проверяет есть ли в текущем модуле указанная команда
--! \param string - команда
--! \return boolean
function hasModuleCommand( command )
	return CurrentModule ~= nil and CurrentModule[command] ~= nil
end



--! \brief Выполнить команду текущего модуля
--! \param string - команда
--! \param args - аргументы функции
--! \return nil
function doModuleCommand( command, ... )
	CurrentModule[command](...)
end



-- returns list of files extensions that are allowed to open
--! \brief Возвращает список расширений, которые модуль обработает автоматически
--! \deprecated
function getExtensions()
	if CurrentModule ~= nil then
		return CurrentModule.getExtensions()
	end
end


-- command Open from main menu
--! \brief Указывает модулю открыть файл
--! \param string - имя файла
--! \return ?
--! \deprecated
function openFile( fileName )
	if CurrentModule ~= nil then
		return CurrentModule.openFile( fileName )
	end
end


-- command Select Version from main menu
--! \brief Выбрать версию игры текущего модуля
--! \return string - версия модуля
function selectVersion()
	if CurrentModule ~= nil then
		if CurrentModule.selectVersion == nil then
			print("There no other versions for currently selected module")
		else
			return CurrentModule.selectVersion()
		end
	end
end



-- command Select Module from main menu
--! \brief Выбрать модуль из доступных и сделать его текущим
--! \return nil
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



--! \brief Установить текущий модуль и путь к игре, которую он поддерживает
function setCurrentModule( moduleName, gamePath )
	print ("setCurrentModule: ", moduleName)

	CurrentModule = UTTModules[ moduleName ]
	CurrentModule["GamePath"] = gamePath

	setModuleReady()
end



--! \brief Установить версию игры текущего модуля
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
