--[[!
	\file 
	\brief Общие функции для всех модулей
	]]



--! \brief Таблица функций чтения буфера
BufferReadFunctions = {}

--! \brief Размеры различных типов в байтах
TypeSize = 
{ 
	CHAR = 1,	BYTE = 1, 
	SHORT = 2,	SHORT_BE = 2, 
	WORD = 2,	WORD_BE = 2, 
	LONG = 4,	LONG_BE = 4, 
	DWORD = 4,	DWORD_BE = 4, 
}

--! \brief Функция возвратит размер типа DATAnnnn, например DATA6 или DATA48
function TypeSize.Get(custom)
	return tonumber(custom:sub(5))
end


originalPrint = print --! сохраним ссылку на print


--! \brief Переопределение стандартного метода печати для вывода в лог
function print( ... )
	originalPrint(...)
	if writeToLog ~= nil then
		logWrite(...)
	end
end



--! \brief Печать непосредственно в лог
function logWrite(...)
	local arg = {...}
	if #arg == 0 then 
		writeToLog( '\n' )
		return
	end
	local printResult = ''
	for i,v in ipairs(arg) do
		printResult = printResult..tostring(v).."\t"
	end
	writeToLog('SCRIPT: '..printResult)
end



--[[

For game versions

]]--



--! \brief Поиск индекса строки в массиве строк
--! \param table - массив строк
--! \param string - строка
--! \return int - индекс в массиве
function findStringInTable( tab, txt )
	for i = 1, #tab do
		if tab[i] == txt then
			return i
		end
	end
end



--! \brief Поиск строки в массиве строк
--! \param table - массив строк
--! \param string - строка или часть строки которую надо найти в массиве
--! \return string - найденная строка или nil
function findAnyStringInTable( tab, txt )
	for i = 1, #tab do
		if string.find(txt, tab[i]) ~= nil then
			return tab[i]
		end
	end
end



--[[

File operations

]]--



--! \brief Проверка доступности файла для чтения
--! \param string - имя файла
--! \return boolean
function fileExist( name )
	local f = io.open(name,"r")
	if f~=nil then 
		io.close(f) 
		return true 
	end
	return false
end



--! \brief Вовращает размер файла
--! \param string - имя файла
--! \return int
function fileSize(filename)
	local fh = assert(io.open(filename, "rb"))
	local len = assert(fh:seek("end"))
	fh:close()
	return len
end



--! \brief Печать таблицы (вспомогательная функция)
--! \param table
function showTable( tab )
	for k, v in pairs( tab ) do
		print(k, v)
	end
end



--! \brief Копирует часть из одного файла в другой
--! \param file - ссылка на открытый файл источник
--! \param file - ссылка на открытый файл приёмник
--! \param int - количество байт, которое надо скопировать
function extractFromFileToFile(srcFile, outFile, size)
	while size > 0 do
		local bufSize = 64000
		
		if bufSize > size then
			bufSize = size
		end
		
		local data = srcFile:read( bufSize )
		outFile:write(data)
		size = size - bufSize
	end
end



--- functions to read strict data structures



--! \brief Функция обрезает лишние нули у строки
--! В случае, когда текстовая строка короче, чем буфер, требуется отрезать завершающие символы
--! от первого встреченного нуля, иначе будут ошибки если продолжить работать с буфером как с обычной строкой.
--! \param string - строка (двоичный буфер)
--! \return string - если ноль не найден, строка будет возвращена без изменений.
function cropZeroes(txt)
	local zeroPos = string.find(txt, '\0')

	if zeroPos then
		return string.sub(txt, 1, zeroPos - 1)
	end
	
	return txt
end



--! \brief Функция чтения байта со знаком
--! \param string - двоичный буфер
function BufferReadFunctions.CHAR( buf )
	return strToChar(buf)
end



--! \brief Функция чтения байта без знака
--! \param string - двоичный буфер
function BufferReadFunctions.BYTE( buf )
	return strToByte(buf)
end


--! \brief Функция чтения слова со знаком
--! \param string - двоичный буфер
function BufferReadFunctions.SHORT( buf )
	return strToShort(buf)
end


--! \brief Функция чтения слова со знаком (Big Endian)
--! \param string - двоичный буфер
function BufferReadFunctions.SHORT_BE( buf )
	return swap16( strToShort(buf) )
end



--! \brief Функция чтения слова без знака
--! \param string - двоичный буфер
function BufferReadFunctions.WORD( buf )
	return strToWord(buf)
end



--! \brief Функция чтения слова без знака (Big Endian)
--! \param string - двоичный буфер
function BufferReadFunctions.WORD_BE( buf )
	return swap16( strToWord(buf) )
end



--! \brief Функция чтения слова (32 bit) со знаком 
--! \param string - двоичный буфер
function BufferReadFunctions.LONG( buf )
	return strToInt(buf)
end



--! \brief Функция чтения слова (32 bit) со знаком  (Big Endian)
--! \param string - двоичный буфер
function BufferReadFunctions.LONG_BE( buf )
	return swap32( strToInt(buf) )
end



--! \brief Функция чтения слова (32 bit) без знака 
--! \param string - двоичный буфер
function BufferReadFunctions.DWORD( buf )
	return strToUint(buf)
end



--! \brief Функция чтения слова (32 bit) без знака (Big Endian)
--! \param string - двоичный буфер
function BufferReadFunctions.DWORD_BE( buf )
	return swap32( strToUint(buf) )
end



--! \brief Функция чтения структур из буфера
--! \param string - двоичный буфер
--! \param table - таблица с описанием структуры (см. примеры)
--! \return table - таблица с числовыми значениями известных типов и двоичный буфер для произвольных
function readDataFromBuffer( buf, dataTable )
	local result = {}
	for i, what in ipairs( dataTable ) do
		for key, value in pairs( what ) do
			if BufferReadFunctions[value] ~= nil then
				result[key] = BufferReadFunctions[value]( buf )
				buf = string.sub(buf, TypeSize[value] + 1)
			else
				local size = TypeSize.Get(value)
				result[key] = string.sub(buf, 1, size)
				buf = string.sub(buf, size + 1)
			end
		end
	end
	return result
end



------------------------



--! \brief Функция чтения структур из файла
--! \param file - дескриптор открытого файла
--! \param table - таблица с описанием структуры (см. примеры)
--! \return table - таблица с числовыми значениями известных типов и двоичный буфер для произвольных
function readData( file, dataTable )
	local result = {}
	
	for i, what in ipairs( dataTable ) do
		for key, value in pairs( what ) do
			if BufferReadFunctions[value] ~= nil then
				local data = file:read( TypeSize[value] )
				
				if not data then
					return
				end
				
				result[key] = BufferReadFunctions[value]( data )
			else
				local size = TypeSize.Get(value)
				local data = file:read( size )
				
				if not data then
					return
				end
				
				result[key] = data
			end
		end
	end
	
	return result
end



--! \brief Функция определения размера структуры
--! \param table - таблица с описанием структуры (см. примеры)
--! \return int - размер в байтах
function getDataSize( dataTable )
	local result = 0
	
	for i, what in ipairs( dataTable ) do
		for key, value in pairs( what ) do
			
			if TypeSize[value] ~= nil then
				result = result + TypeSize[value]
			else	-- for parameters like DATA8 or DATA456
				local number = value:sub(5)
				result = result + tonumber(number)
			end
			
		end
	end
	
	return result
end




