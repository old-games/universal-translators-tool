ReadFunctions = { }
BufferReadFunctions = {}
TypeSize = 
{ 
	CHAR = 1,	BYTE = 1, 
	SHORT = 2,	SHORT_BE = 2, 
	WORD = 2,	WORD_BE = 2, 
	LONG = 4,	LONG_BE = 4, 
	DWORD = 4,	DWORD_BE = 4, 
}

originalPrint = print



function print( ... )
	originalPrint(...)
	if writeToLog ~= nil then
		logWrite(...)
	end
end



-- wxLogMessage
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



function findStringInTable( tab, txt )
	for i = 1, #tab do
		if tab[i] == txt then
			return i
		end
	end
end



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



function fileExist( name )
	local f = io.open(name,"r")
	if f~=nil then 
		io.close(f) 
		return true 
	end
	return false
end



function fileSize(filename)
	local fh = assert(io.open(filename, "rb"))
	local len = assert(fh:seek("end"))
	fh:close()
	return len
end



function showTable( tab )
	for k, v in pairs( tab ) do
		print(k, v)
	end
end



--- functions to read strict data structures



function BufferReadFunctions.CHAR( buf )
	return strToChar(buf)
end



function BufferReadFunctions.BYTE( buf )
	return strToByte(buf)
end



function BufferReadFunctions.SHORT( buf )
	return strToShort(buf)
end



function BufferReadFunctions.SHORT_BE( buf )
	return swap16( strToShort(buf) )
end



function BufferReadFunctions.WORD( buf )
	return strToWord(buf)
end



function BufferReadFunctions.WORD_BE( buf )
	return swap16( strToWord(buf) )
end



function BufferReadFunctions.LONG( buf )
	return strToInt(buf)
end



function BufferReadFunctions.LONG_BE( buf )
	return swap32( strToInt(buf) )
end



function BufferReadFunctions.DWORD( buf )
	return strToUint(buf)
end



function BufferReadFunctions.DWORD_BE( buf )
	return swap32( strToUint(buf) )
end



function readDataFromBuffer( buf, dataTable )
	local result = {}
	for i, what in ipairs( dataTable ) do
		for key, value in pairs( what ) do
			result[key] = BufferReadFunctions[value]( buf )
			buf = string.sub(buf, TypeSize[value] + 1)
		end
	end
	return result
end



------------------------



function ReadFunctions.DATA8( file )
	return file:read( 8 )
end



function ReadFunctions.DATA9( file )
	return file:read( 9 )
end



function readData( file, dataTable )
	local result = {}
	for i, what in ipairs( dataTable ) do
		for key, value in pairs( what ) do
			if BufferReadFunctions[value] ~= nil then 
				result[key] = BufferReadFunctions[value]( file:read( TypeSize[value] ) )
			else
				result[key] = ReadFunctions[value]( file )
			end
		end
	end
	return result
end




