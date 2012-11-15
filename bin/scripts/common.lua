ReadFunctions = { }

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



function ReadFunctions.WORD( file )
	local block = 2
	local bytes = file:read( 2 )
	return bytes:byte(2) * 256 + bytes:byte(1)
end



function ReadFunctions.LONG( file )
	local block = 4
	local bytes = file:read( 4 )
	return bytes:byte(4) * 16777216 + bytes:byte(3) * 65536 + bytes:byte(2) * 256 + bytes:byte(1)
end



function ReadFunctions.DWORD( file )
	return ReadFunctions.LONG(file)
end



function readData( file, dataTable )
	local result = {}
	for i, what in ipairs( dataTable ) do
		for key, value in pairs( what ) do
			result[key] = ReadFunctions[value]( file )
		end
	end
	return result
end





