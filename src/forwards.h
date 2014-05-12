/***************************************************************
 * Name:      forwards.h
 * Purpose:   forward declarations
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2014-05-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

class Palette;
typedef std::shared_ptr<Palette> PalettePtr;

class IndexMask;
typedef std::shared_ptr<IndexMask> IndexMaskPtr;

class Origin;
typedef std::shared_ptr<Origin> OriginPtr;
typedef std::weak_ptr<Origin> WeakOriginPtr;

class IInfo;
typedef std::shared_ptr<IInfo> IInfoPtr;

class ImageInfo;
typedef std::shared_ptr<ImageInfo> ImageInfoPtr;

class SymbolInfo;
typedef std::shared_ptr<SymbolInfo> SymbolInfoPtr;
typedef wxVector<SymbolInfoPtr> Symbols;

class FontInfo;
typedef std::shared_ptr<FontInfo> FontInfoPtr;

class LibTree;
typedef std::shared_ptr<LibTree> LibTreePtr;

class Animation;
typedef std::shared_ptr<Animation> AnimationPtr;

class Sound;
typedef std::shared_ptr<Sound> SoundPtr;

class Video;
typedef std::shared_ptr<Video> VideoPtr;



