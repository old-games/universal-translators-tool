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
		print (tab[i], txt)
		if string.find(txt, tab[i]) ~= nil then
			print ("Found ", tab[i])
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



function ReadFunctions.BYTE( file )
	local bytes = file:read( 1 )
	return bytes:byte(1)
end



function ReadFunctions.WORD( file )
	local bytes = file:read( 2 )
	return bytes:byte(2) * 256 + bytes:byte(1)
end



function ReadFunctions.LONG( file )
	local bytes = file:read( 4 )
	return bytes:byte(4) * 16777216 + bytes:byte(3) * 65536 + bytes:byte(2) * 256 + bytes:byte(1)
end



function ReadFunctions.DWORD( file )
	return ReadFunctions.LONG(file)
end



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
			result[key] = ReadFunctions[value]( file )
		end
	end
	return result
end





