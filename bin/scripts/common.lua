BufferReadFunctions = {}

TypeSize = 
{ 
	CHAR = 1,	BYTE = 1, 
	SHORT = 2,	SHORT_BE = 2, 
	WORD = 2,	WORD_BE = 2, 
	LONG = 4,	LONG_BE = 4, 
	DWORD = 4,	DWORD_BE = 4, 
}

function TypeSize.Get(custom)
	-- for parameters like DATA8 or DATA456
	return tonumber(custom:sub(5))
end


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



function createSolidData( file, dataTable )
end


