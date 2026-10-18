//
// worldgen/biome/biome.cpp
// 2026-10-17
// dungeon_of_the_cod
//


#include "worldgen/biome/biome.h"
#include "worldgen/biome/biome_lookup.h"
#include <cmath>
#define PI 3.14159265

#define DX 0.03125
#define EVIL_BLOWUP_FACTOR 4.16

float Terrain::ELEVATION(float x, float y, int lod){
    return __ELEVATION.octave2D_01(x * __ELEVATION_SCALE, y * __ELEVATION_SCALE, lod);
}

float Terrain::SURFACE_ELEVATION(float x, float y, int lod){
    return std::max(__SEA_FLOAT,ELEVATION(x,y,lod));
}

float Terrain::RAINFALL(float x, float y){
    const int EL_LOD = 3; // to avoid silly locality issues
    float rv = 0.5 + __RAINFALL_VARIATION.octave2D_11(x * __RAIN_SCALE, y * __RAIN_SCALE, __RAIN_OCTAVES)/3;
    float sel = SURFACE_ELEVATION(x,y,EL_LOD);
    // rain shadow factor
    {
        float latitude = sin(latitude_behavior_displacement + y*((2*PI)/latitude_behavior_period));
        float wind_factor;
        if (latitude < 0.5 && latitude > -0.5){
            if (latitude < 0){
                wind_factor = 0.5+latitude;
            } else {
                wind_factor = 0.5-latitude;
            }
        // westerlies in temperate areas
            rv += wind_factor*(sel - SURFACE_ELEVATION(x-DX,y,EL_LOD))/(DX*2.0);
        } else {
            if (latitude < 0) {
                latitude = -latitude;
            }
            wind_factor = latitude - 0.5;
        // easterlies in polar and tropical areas
            rv += wind_factor*(sel - SURFACE_ELEVATION(x+DX,y,EL_LOD))/(DX*2.0);
        }
    }
    rv -= (sel - __SEA_FLOAT)/3.0;

    return rv;
}
float Terrain::TEMPERATURE(float x, float y){
    float tv = __TEMPERATURE_VARIATION.octave2D_11(x * __TEMP_SCALE, y * __TEMP_SCALE, __TEMP_OCTAVES);
    tv -= (SURFACE_ELEVATION(x,y)-__SEA_FLOAT)/2;
    tv += sin(latitude_behavior_displacement + y*((2*PI)/latitude_behavior_period))*0.9;
    //tv += 0; // constant fudge factor
    return tv/2.1;
}

float Terrain::ALIGNMENT(float x, float y){
    float al = __ALIGNMENT.octave2D_11(x * __ALIGNMENT_SCALE, y * __ALIGNMENT_SCALE, __ALIGNMENT_OCTAVES);
    al -= std::log(x*x + y*y+1)/EVIL_BLOWUP_FACTOR;
    return al + 0.3;
}

float Terrain::MAGIC(float x, float y){
    return __MAGIC.octave2D_01(x * __MAGIC_SCALE, y * __MAGIC_SCALE, __MAGIC_OCTAVES);
}

Terrain::Terrain(uint32_t seed){
    __SEED = seed;
    std::mt19937 mt(seed); 
    __ELEVATION = siv::PerlinNoise { mt() };
    __RAINFALL_VARIATION = siv::PerlinNoise { mt() };
    __TEMPERATURE_VARIATION = siv::PerlinNoise { mt() };
    __MAGIC = siv::PerlinNoise { mt() };
    __ALIGNMENT = siv::PerlinNoise { mt() };

    __ELEVATION_SCALE = 1.0;
    __RAIN_SCALE = 1.0/4;
    __TEMP_SCALE = 1.0/4;
    __ALIGNMENT_SCALE = 1.0/3;
    __MAGIC_SCALE = 1.0/8;

    TILE_SCALE = 1.0/256;

    max_elevation = 256; 
    min_elevation = -255; 
    sea_level = 40;
    latitude_behavior_displacement = mt()*(1.5/std::numeric_limits<uint32_t>::max())-1.0;

    __SEA_FLOAT = (sea_level-min_elevation)*1.0/(max_elevation-min_elevation);
}

void Terrain::export_images(int32_t centerx, int32_t centery, int scale){
    std::string fnb;
    std::stringstream filenamebase;
    Image image{ 512, 512 };
    filenamebase << "img/" << __SEED << 'x' << centerx << 'y' << centery << 's' << scale;
    filenamebase >> fnb;
    // elevation
    {
        std::stringstream ss;
        ss << fnb << "elevation" << ".bmp";
        for (std::int32_t y = 0; y < image.height(); ++y)
		{
			for (std::int32_t x = 0; x < image.width(); ++x)
			{
                int scaled_x = (x - image.width()/2) * scale + centerx; 
                int scaled_y = (y - image.height()/2) * scale + centery;
                float el = ELEVATION(scaled_x*TILE_SCALE,scaled_y*TILE_SCALE);
                bool undersea = (el*(max_elevation - min_elevation) + min_elevation < sea_level);
				const RGB color(undersea?0:el, undersea?0:el, el);
				image.set(x, y, color);
			}
		}

        if (image.saveBMP(ss.str()))
		{
			std::cout << "...saved \"" << ss.str() << "\"\n";
		}
		else
		{
			std::cout << "...failed\n";
		}
    }
    // temperature
    {
        std::stringstream ss;
        ss << fnb << "temp" << ".bmp";
        for (std::int32_t y = 0; y < image.height(); ++y)
		{
			for (std::int32_t x = 0; x < image.width(); ++x)
			{
                int scaled_x = (x - image.width()/2) * scale + centerx; 
                int scaled_y = (y - image.height()/2) * scale + centery;
                float temp = TEMPERATURE(scaled_x*TILE_SCALE,scaled_y*TILE_SCALE);

				const RGB color((temp > 0)?temp:0, 0, (temp < 0)?-temp:0);
				image.set(x, y, color);
			}
		}

        if (image.saveBMP(ss.str()))
		{
			std::cout << "...saved \"" << ss.str() << "\"\n";
		}
		else
		{
			std::cout << "...failed\n";
		}
    }
    // rainfall
    {
        std::stringstream ss;
        ss << fnb << "rf" << ".bmp";
        for (std::int32_t y = 0; y < image.height(); ++y)
		{
			for (std::int32_t x = 0; x < image.width(); ++x)
			{
                int scaled_x = (x - image.width()/2) * scale + centerx; 
                int scaled_y = (y - image.height()/2) * scale + centery;
                float rf = RAINFALL(scaled_x*TILE_SCALE,scaled_y*TILE_SCALE);

				const RGB color((rf>0.5)?0:2*(0.5-rf), (rf>0.5)?2*(rf-0.5):2*(0.5-rf), 0);
				image.set(x, y, color);
			}
		}

        if (image.saveBMP(ss.str()))
		{
			std::cout << "...saved \"" << ss.str() << "\"\n";
		}
		else
		{
			std::cout << "...failed\n";
		}
    }
    // alignment
    {
        std::stringstream ss;
        ss << fnb << "algn" << ".bmp";
        for (std::int32_t y = 0; y < image.height(); ++y)
		{
			for (std::int32_t x = 0; x < image.width(); ++x)
			{
                float max_bad = 1+std::log(image.width()*scale/(0.2*TILE_SCALE))/EVIL_BLOWUP_FACTOR;
                int scaled_x = (x - image.width()/2) * scale + centerx; 
                int scaled_y = (y - image.height()/2) * scale + centery;
                float temp = ALIGNMENT(scaled_x*TILE_SCALE,scaled_y*TILE_SCALE);

				const RGB color((temp < 0)?(-temp)/max_bad:0,(temp > 0)?temp:0, 0);
				image.set(x, y, color);
			}
		}

        if (image.saveBMP(ss.str()))
		{
			std::cout << "...saved \"" << ss.str() << "\"\n";
		}
		else
		{
			std::cout << "...failed\n";
		}
    }
    // magic
    {
        std::stringstream ss;
        ss << fnb << "mgc" << ".bmp";
        for (std::int32_t y = 0; y < image.height(); ++y)
		{
			for (std::int32_t x = 0; x < image.width(); ++x)
			{
                int scaled_x = (x - image.width()/2) * scale + centerx; 
                int scaled_y = (y - image.height()/2) * scale + centery;
                float temp = MAGIC(scaled_x*TILE_SCALE,scaled_y*TILE_SCALE);

				const RGB color(temp,0,temp);
				image.set(x, y, color);
			}
		}

        if (image.saveBMP(ss.str()))
		{
			std::cout << "...saved \"" << ss.str() << "\"\n";
		}
		else
		{
			std::cout << "...failed\n";
		}
    }
    // biomes
    {
        std::stringstream ss;
        ss << fnb << "biome" << ".bmp";
        for (std::int32_t y = 0; y < image.height(); ++y)
		{
			for (std::int32_t x = 0; x < image.width(); ++x)
			{
                int scaled_x = (x - image.width()/2) * scale + centerx; 
                int scaled_y = (y - image.height()/2) * scale + centery;
                std::string b = biome_lookup(ELEVATION(scaled_x*TILE_SCALE,scaled_y*TILE_SCALE), TEMPERATURE(scaled_x*TILE_SCALE,scaled_y*TILE_SCALE), RAINFALL(scaled_x*TILE_SCALE,scaled_y*TILE_SCALE), ALIGNMENT(scaled_x*TILE_SCALE,scaled_y*TILE_SCALE), MAGIC(scaled_x*TILE_SCALE,scaled_y*TILE_SCALE), __SEA_FLOAT);
				RGB color = biome_color(b);
				image.set(x, y, color);
			}
		}

        if (image.saveBMP(ss.str()))
		{
			std::cout << "...saved \"" << ss.str() << "\"\n";
		}
		else
		{
			std::cout << "...failed\n";
		}
    }
}