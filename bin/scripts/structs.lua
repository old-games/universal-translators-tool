--1      2        Height         Image height (Big endian)
--2      2        Width          Image width (Big endian)
--3      2        x-orig         Where on screen, in pixels, the image's top-left corner is. Value is
--4      2        y-orig         usually 0,0 unless image is part of a larger image or not fullscreen.
--5      1        Planes         Number of planes in bitmap, 1 for monochrome, 4 for 16 color, 8 for 256 color
--                               If 0 we have a colormap
--6      1        Mask           1 = masked, 2 = transparent color, 3 = lasso (For MacPaint) Mask data is not
--                               considered a bit plane
--7      2        Compression    If 1 then image data is RLE compressed
--8      2        Trans color    Transparent color, useful only for Mask > 1
--9      1        xAspect        Pixel aspect, a ratio width:height; used for displaying the image
--10     1        yAspect        on a variety of different screen resolutions for 320x200 5:6 or 10:11
--11     2        PageWidth      The size of the screen the image is to be displayed on, in pixels,
--12     2        PageHeight     Usually 320x200

--! \brief Структура заголовка LBM файла
LBMHeader = {}
LBMHeader[1] = { WIDTH 			= "WORD_BE"	}
LBMHeader[2] = { HEIGHT			= "WORD_BE"	}
LBMHeader[3] = { X 				= "WORD_BE"	}
LBMHeader[4] = { Y 				= "WORD_BE"	}
LBMHeader[5] = { BPP			= "BYTE" 	}
LBMHeader[6] = { MASK 			= "BYTE" 	}
LBMHeader[7] = { COMPRESSION	= "WORD" 	}
LBMHeader[8] = { TRANSPARENT	= "WORD_BE"	}
LBMHeader[9] = { XASPECT		= "BYTE" 	}
LBMHeader[10] = { YASPECT		= "BYTE" 	}
LBMHeader[11] = { PAGEWIDTH		= "WORD_BE"	}
LBMHeader[12] = { PAGEHEIGHT 	= "WORD_BE"	}



BMPFileHeader = {}
BMPFileHeader[1] = { ID 		= "WORD" 	}
BMPFileHeader[2] = { FILESIZE 	= "LONG" 	}
BMPFileHeader[3] = { RESERVED1 	= "WORD" 	}
BMPFileHeader[4] = { RESERVED2 	= "WORD" 	}
BMPFileHeader[5] = { DATAOFFSET = "DWORD" 	}



BMPInfoHeader = {}
BMPInfoHeader[1] 	= { DATASIZE		= "DWORD" 	}
BMPInfoHeader[2] 	= { WIDTH			= "LONG" 	}
BMPInfoHeader[3] 	= { HEIGHT			= "LONG" 	}
BMPInfoHeader[4] 	= { PLANES			= "WORD" 	}
BMPInfoHeader[5] 	= { BITCOUNT		= "WORD" 	}
BMPInfoHeader[6] 	= { COMPRESSION 	= "DWORD" 	}
BMPInfoHeader[7] 	= { SIZEIMAGE		= "DWORD" 	}
BMPInfoHeader[8] 	= { XPELSPERMETER	= "LONG" 	}
BMPInfoHeader[9] 	= { YPELSPERMETER	= "LONG" 	}
BMPInfoHeader[10] 	= { CLRUSED			= "DWORD" 	}
BMPInfoHeader[11] 	= { CLRIMPORTANT	= "DWORD" 	}
