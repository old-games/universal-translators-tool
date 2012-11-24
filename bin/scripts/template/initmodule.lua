local ModuleName = 'template'

local Template = {}

gameVersions = { 'template1', 'template2' }

local ActionsOnExtension = 
{ 
	ext = "loadEXT"
}

local currentVersion = 0

local Operations = {}



UTTModules[ModuleName] = Template



function Template.selectVersion()
	local res = selectVersionDialog( gameVersions )
	res = findStringInTable( gameVersions, res )
	if res ~= nil then
		currentVersion = res
		setModuleReady()
	end
end



function Template.getModuleName()
	return gameVersions[currentVersion]
end



function Template.getExtensions()
	return '*.* (*.*)|*.*'
end



function Template.openFile( fileName )
	local fileName = string.lower( fileName )
	local vol, path, name, ext = parseFileName( fileName )
	local key = ActionsOnExtension[ ext ]
	if key == nil then
		print( "Can't find function for '"..ext.."' extension" )
		return
	end
	Operations[ key ]( fileName )
end



function Operations.loadEXT( filename )
	local vol, path, name, ext = parseFileName( filename )
	path = vol..path..'/'

	local fh = assert(io.open(filename, "rb"))
	if not fh then
		return
	end
	 
	fh:close()
end




print "Template module loaded? No need to do it"
