# WallpaperLite

UI wrapper for [WallpaperLite-CLI](https://github.com/LincolnCox29/WallpaperLite-CLI) 

**Set videos as your Windows desktop wallpaper** using VLC's lightweight engine. Perfect for animated backgrounds with minimal resource usage.

![GitHub Stars](https://img.shields.io/github/stars/MHSPlay/Wallpaper-Lite?style=for-the-badge&logo=github)
![GitHub Forks](https://img.shields.io/github/forks/MHSPlay/Wallpaper-Lite?style=for-the-badge&logo=github)
![GitHub Last Commit](https://img.shields.io/github/last-commit/MHSPlay/Wallpaper-Lite?style=for-the-badge&logo=git)
![GitHub Releases](https://img.shields.io/github/downloads/MHSPlay/Wallpaper-Lite/total?style=for-the-badge&logo=github)

## 🎦 CLI Version
- https://github.com/LincolnCox29/WallpaperLite-CLI
- By [LincolCox29](https://github.com/LincolnCox29) and [MHSPlay](https://github.com/MHSPlay)

## 📌 Features
- Hardware-accelerated video playback (DXVA2)
- Seamless desktop integration via `WorkerW` injection
- Loop playback with audio disabled
- Windows 10/11 support
- C/C++ only

## 🚀 Installation
1. Download [__latest release__](https://github.com/MHSPlay/Wallpaper-Lite/releases)
2. Run __Wallpaper-Lite.exe__

## ⚙️ Performance Considerations
**GPU load depends critically on your video source properties**:
```markdown
|-----------------|----------------------------|----------------------------|-------------------------|
| Factor          | Low Load                   | High Load                  | Recommendation          |
|-----------------|----------------------------|----------------------------|-------------------------|
|   Format        | MP4, MKV                   | AVI, MOV                   | Use MP4 containers      |
|   Resolution    | ≤ Screen resolution        | 4K/8K                      | Match desktop resolution|
|   Bitrate       | 5-15 Mbps (1080p)          | 50+ Mbps                   | ≤20 Mbps for 1080p      |
|   Codec         | H.264 (AVC)                | HEVC, VP9, AV1             | Prefer H.264            |
|   FPS           | 24-30 FPS                  | 60-120 FPS                 | Cap at 30 FPS           |
|-----------------|----------------------------|----------------------------|-------------------------|
```

## 🐛 Known Limitations
- No volume control (audio disabled)
- Single monitor support only
- Windows only
