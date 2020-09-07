#pragma once

#include <vector>

/// <summary>
/// An RGB bitmap renderer.
/// </summary>
class BitmapRenderer
{
private:
    /// <summary>
    /// The width of the bitmap in pixels.
    /// </summary>
    size_t width;

    /// <summary>
    /// The height of the bitmap in pixels.
    /// </summary>
    size_t height;

    /// <summary>
    /// The bitmap.
    /// Pixels are stored in RGB format with one byte per component, and in row-major order left to right and bottom to top.
    /// </summary>
    std::vector<uint8_t> bitmap;

public:
    /// <summary>
    /// Constructs a BitmapRenderer.
    /// </summary>
    /// <param name="width">The width of the bitmap in pixels.</param>
    /// <param name="height">The height of the bitmap in pixels.</param>
    /// <param name="bitmap">
    /// The bitmap.
    /// Pixels are stored in RGB format with one byte per component, and in row-major order left to right and bottom to top.
    /// </param>
    BitmapRenderer (size_t width, size_t height, std::vector<uint8_t>&& bitmap);

    /// <summary>
    /// Renders the bitmap to a new GLFW window and waits for the user to close the window.
    /// </summary>
    void Render () const;
};
