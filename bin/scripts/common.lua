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
	local bufCounter = 0
	for i, what in ipairs( dataTable ) do
		for key, value in pairs( what ) do
			print (string.sub(buf, bufCounter, TypeSize[value] + 1 ) )
			result[key] = BufferReadFunctions[value]( buf, string.sub(buf, bufCounter, TypeSize[value] + 1 ) )
			--print (buf, TypeSize[value], value)
			bufCounter = bufCounter + TypeSize[value] + 1 
		end
	end
	return result
end



------------------------

--
--function ReadFunctions.CHAR( file )
--	return BufferReadFunctions.CHAR( file:read( TypeSize.CHAR ) )
--end
--
--
--function ReadFunctions.BYTE( file )
--	return BufferReadFunctions.BYTE( file:read( TypeSize.BYTE ) )
--end
--
--
--
--function ReadFunctions.SHORT( file )
--	return BufferReadFunctions.SHORT( file:read( TypeSize.SHORT ) )
--end
--
--
---- BigEndian
--function ReadFunctions.SHORT_BE( file )
--	return BufferReadFunctions.SHORT_BE( file:read( TypeSize.SHORT_BE ) )
--end
--
--
--
--function ReadFunctions.WORD( file )
--	return BufferReadFunctions.WORD( file:read( TypeSize.WORD ) )
--end
--
--
---- BigEndian
--function ReadFunctions.WORD_BE( file )
--	return BufferReadFunctions.WORD_BE( file:read( TypeSize.WORD_BE ) )
--end
--
--
--
--function ReadFunctions.LONG( file )
--	return BufferReadFunctions.LONG( file:read( TypeSize.LONG ) )
--end
--
--
---- BigEndian
--function ReadFunctions.LONG_BE( file )
--	return BufferReadFunctions.LONG_BE( file:read( TypeSize.LONG_BE ) )
--end
--
--
--
--function ReadFunctions.DWORD( file )
--	return BufferReadFunctions.DWORD( file:read( TypeSize.DWORD ) )
--end
--
--
---- BigEndian
--function ReadFunctions.DWORD_BE( file )
--	return BufferReadFunctions.DWORD_BE( file:read( TypeSize.DWORD_BE ) )
--end



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




