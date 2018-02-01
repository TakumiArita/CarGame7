xof 0303txt 0032
template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template ObjectMatrixComment {
 <95a48e28-7ef4-4419-a16a-ba9dbdf0d2bc>
 Matrix4x4 objectMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}


Frame straight {
 

 FrameTransformMatrix relative {
  1.000000,0.000000,0.000000,0.000000,0.000000,-0.000001,1.000000,0.000000,0.000000,-1.000000,-0.000001,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 ObjectMatrixComment object {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh mesh_s {
  10;
  0.000000;-0.000001;-1.000000;,
  19.000000;-0.000001;-1.000000;,
  19.000000;-40.000000;-0.999974;,
  0.000000;-40.000000;-0.999974;,
  20.000000;0.000000;0.000000;,
  20.000000;-40.000000;0.000026;,
  -19.000000;-40.000000;-0.999974;,
  -19.000000;-0.000001;-1.000000;,
  -20.000000;0.000000;0.000000;,
  -20.000000;-40.000000;0.000026;;
  8;
  3;0,1,2;,
  3;2,3,0;,
  3;4,5,2;,
  3;2,1,4;,
  3;0,3,6;,
  3;6,7,0;,
  3;8,7,6;,
  3;6,9,8;;

  MeshNormals normals {
   10;
   0.000000;-0.000001;-1.000000;,
   0.382683;-0.000001;-0.923879;,
   0.382683;-0.000001;-0.923879;,
   0.000000;-0.000001;-1.000000;,
   0.707107;0.000000;-0.707107;,
   0.707107;0.000000;-0.707107;,
   -0.382683;-0.000001;-0.923880;,
   -0.382683;-0.000001;-0.923880;,
   -0.707107;0.000000;-0.707107;,
   -0.707107;0.000000;-0.707107;;
   8;
   3;0,1,2;,
   3;2,3,0;,
   3;4,5,2;,
   3;2,1,4;,
   3;0,3,6;,
   3;6,7,0;,
   3;8,7,6;,
   3;6,9,8;;
  }

  MeshTextureCoords tc0 {
   10;
   0.999900;0.999900;,
   0.049805;1.000000;,
   0.049805;0.000000;,
   0.999900;0.000100;,
   0.000000;1.000000;,
   0.000000;0.000000;,
   0.049805;0.000000;,
   0.049805;1.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;;
  }

  MeshMaterialList mtls {
   1;
   8;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;

   Material Dflt_Material {
    0.640000;0.640000;0.640000;1.000000;;
    36.205862;
    0.500000;0.500000;0.500000;;
    0.000000;0.000000;0.000000;;

    TextureFilename Diffuse {
     "asphalt_road_albedo.png";
    }
   }
  }
 }
}