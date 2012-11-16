require 'xcom/xcom'

local ModuleName = 'xcom'
local Xcom = {}

gameVersions = { 'UFO 1 (DOS)', 'UFO 2 (WIN)' }
local currentVersion = 2

local ActionsOnExtension = 
{ 
	dat = "loadDAT"
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
	return 'BIGLETS.DAT (biglets.dat)|biglets.dat|SMALLSET.DAT (smallset.dat)|smallset.dat'
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

	local fh = assert(io.open(filename, "rb"))
	if not fh then
		return
	end
	
	path = vol..path..'/'
	local exec = xcomFontInfo[currentVersion].execInfo
	
	local params = xcomFontInfo[currentVersion][name]
	local width = params.width
	local height = params.height
	local bufsize = width * height
	local num = 0
	local font = FontInfo:new()
	
	local symWidths = GetFontWidth(path.."../"..exec.name, 
		params.offset, params.num, name == 'bitlets')
	
	font:SetValues( width, height, 3, 3, 0, params.baseLine, 0, params.smallLine )
	
	local palBuffer = GetXComPalette(path, params.palette)
	if palBuffer ~= nil then
		pal = Palette:new()
		if pal:Initiate( Palette.bpp8, palBuffer, Palette.sfPlain, true ) then
			font:SetPalette( pal )
		end
	end
	
	print "Font loading..."
	
	repeat
		local bytes = fh:read( bufsize )
		if bytes ~= nil and bytes:len() == bufsize then
			num = num + 1
			local w = width
			if symWidths ~= nil and num <= #symWidths then
				w = string.byte( string.sub(symWidths, num, num) )
			end
			font:AddSymbol( bytes, width, height, w, height )
		end
	until not bytes
	
	print ("Symbols: ", num)
	fh:close()
	editFont( font )
end






print 'Xcom module loaded'
