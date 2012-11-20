require 'xcom/xcom'

local ModuleName = 'xcom'
local Xcom = {}

gameVersions = { 'UFO 1 (DOS)', 'UFO 2 (WIN)' }

local ActionsOnExtension = 
{ 
	dat = "loadDAT",
	scr = "loadDAT"
}



local Operations = {}



UTTModules[ModuleName] = Xcom



function Xcom.selectVersion()
	local res = selectVersionDialog( gameVersions )
	res = findStringInTable( gameVersions, res )
	if res ~= nil then
		currentVersion = res
		setModuleReady()
	end
end



function Xcom.getModuleName()
	return gameVersions[currentVersion]
end



function Xcom.getExtensions()
	return '*.DAT (*.dat)|*.dat|*.SCR (*.scr)|*.scr'
end



function Xcom.openFile( fileName )
	local fileName = string.lower( fileName )
	local vol, path, name, ext = parseFileName( fileName )
	local key = ActionsOnExtension[ ext ]
	if key == nil then
		print( "Can't find function for '"..ext.."' extension" )
		return
	end
	Operations[ key ]( fileName )
end



function Operations.loadDAT( filename )
	--local busy = BusyCursor:new()
	
	local vol, path, name, ext = parseFileName( filename )
	path = vol..path..'/'

	local fh = assert(io.open(filename, "rb"))
	if not fh then
		return
	end
	
	 
	if name == 'biglets' or name == 'smallset' then
		LoadXcomFont( path, name, fh )
	else
--		local found = false
--		for i, #KnownImageNames do
--			if KnownImageNames[i] == name then
--				found = true
--			end
--		end
		local key = findAnyStringInTable( KnownImageNames, name )
		if key ~= nil then
			LoadXcomImage( path, name, key, fh )
		else
			print ("I don't know what to do with ", filename)
		end
	end
	fh:close()
end






print 'Xcom module loaded'
