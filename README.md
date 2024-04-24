#  Khaotic Engine - C++ Custom Engine

Khaotic Engine est un moteur de rendu fait en **C++** réalisé par une petite équipe dans le but d'apprendre à utiliser les API de rendu (OpenGL,DirectX 11/12 et Vulkan).

Ce moteur est basé sur **DirectX11** utilise **ImGui** et **Boost** avec une couche d'abstraction pour permetre son usage avec d'autres API.

---

Khaotic Engine is a rendering engine made in **C++** by a small team with the aim of learning how to use rendering APIs (OpenGL, DirectX 11/12 and Vulkan).

This **DirectX11** based engine uses **ImGui** with an abstraction layer to enable its use with other APIs.

## Installation

Pré-requis pour le moteur:

- Télécharger la librairie Boost v.1_85_0 (Pour utilier python avec le c++)
- Ouvrez un terminal, placer vous dans le dossier boost que vous venez d'extraire et entrez ces commandes bash pour build Boost

```bash
  cd tools/build
  bootstrap vc143
  .\b2
```

- Une fois fait importer les dossiers "boost" et "libs" présent dans le dossier boost_x_xx_x dans le moteur.
- Placer "boost" dans le dossier "enginecustom/include" du moteur.
- Plaer "libs" dans le dossier "enginecustom/libs/boost_lib"
- Vous pouvez ouvrir visual studio est lancer le moteur

----

**From solution + Debugger**

 1.  Download the Beta Release
 2.  Unzip the Zip file
 3.  Open the .sln file
 4. Set the debugger in "Release"
 5.  Launch the debugger



## Shaders list:


 - **Diffuse Lighting**
 - **Ambiant Lighting**
 - **Specular Lighting**
 - **Light Shader**
 - **Light Map Shader**
 - **Alpha Mapping**
 - **Normal Mapping**
 - **Specular Mapping**
 - **Clipping Planes** 
 - **Texture Translation** 
 - **Transparency**
 - **Water**
   - **Refraction**
   - *Reflection (cassé / broken)*
 - *Glace (cassé / broken)*
 - *Verre (cassé / broken)*
 

*Plus de shaders seront disponibles dans le futur*

---

*More shaders will be added in the future*



## ImGui:

*Cette partie du moteur est encore en développement, d'autres fonctionnalitées seront ajoutées dans le futur*

La librairie ImGui est utilisée afin d'interragir avec les éléments du moteur comme les objets.

### Fonctionnalitées:
- Importer des objets 3D sous format **.obj**
- Ajout d'un cube à la scène
- Modifier les propriétées d'un objet (Position, Rotation, Taille)
- Modifier les objets présents dans la scène
- Création d'un terrain
- Modifier les propriétées des lumières (Position, Couleur RVB)

----
*This part of the engine is still in development, other features will be added in the future*

ImGui is used to allow interaction between the user and the objects in the scene.

### Features:
- Import 3D objects with the **.obj** format
- Can add a cube to the scene
- Edit an object properties (Position, Rotation, Scale)
- Edit objects in the current scene
- Terrain generation
- Edit lights properties (Position, RGB Color)



## Demo :

[![Demo Video](https://img.youtube.com/vi/qCOCTyB_97c/0.jpg)](https://www.youtube.com/watch?v=qCOCTyB_97c)


## Bug Report :

Vous pouvez signalez les problèmes en ouvrant un ticket dans [Issues](https://github.com/GamingCampus-AdrienBourgois/khaotic-engine/issues)

----
You can report bugs with the program by creating a ticket in [Issues](https://github.com/GamingCampus-AdrienBourgois/khaotic-engine/issues)

## Engine Build by :

[](https://github.com/GamingCampus-AdrienBourgois/khaotic-engine?tab=readme-ov-file#engine-build-by-)

-   [@CatChow0](https://github.com/CatChow0)
-   [@miragefr0st](https://github.com/miragefr0st)
-   [@StratiX0](https://github.com/StratiX0)
-   [@Kagutsuchi84](https://github.com/Mattys8423)
-   [@Harpie94](https://github.com/Harpie94)
-   [@axelpicou](https://github.com/axelpicou)
-   [@GolfOcean334](https://github.com/GolfOcean334)
-  [@sutabasuto](https://github.com/sutabasuto)





