xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 144;
 2.34635;-0.39777;-0.29643;,
 1.94086;-0.43287;-0.32601;,
 1.96711;-0.25300;-0.40698;,
 2.43829;-0.24298;-0.32601;,
 1.44268;-0.44341;-0.33489;,
 1.44268;-0.25762;-0.42897;,
 0.94449;-0.43287;-0.32601;,
 0.91825;-0.25300;-0.40698;,
 0.53901;-0.39777;-0.29643;,
 0.44706;-0.24298;-0.32601;,
 1.97920;-0.05282;-0.42897;,
 2.46593;-0.05282;-0.33489;,
 1.44268;-0.05281;-0.45756;,
 0.90616;-0.05282;-0.42897;,
 0.41943;-0.05282;-0.33489;,
 1.96711;0.14736;-0.40698;,
 2.43829;0.13735;-0.32601;,
 1.44268;0.15198;-0.42897;,
 0.91825;0.14736;-0.40698;,
 0.44706;0.13735;-0.32601;,
 1.94086;0.32724;-0.32601;,
 2.34635;0.29214;-0.29643;,
 1.44268;0.33777;-0.33489;,
 0.94449;0.32724;-0.32601;,
 0.53901;0.29214;-0.29643;,
 0.53901;-0.39777;-0.29643;,
 0.44706;-0.43287;-0.16603;,
 0.19524;-0.25300;-0.17447;,
 0.44706;-0.24298;-0.32601;,
 0.41943;-0.44341;-0.00582;,
 0.12689;-0.25762;-0.00582;,
 0.44706;-0.43287;0.15439;,
 0.19524;-0.25300;0.16284;,
 0.53901;-0.39777;0.28480;,
 0.44706;-0.24298;0.31437;,
 0.12689;-0.05282;-0.17836;,
 0.41943;-0.05282;-0.33489;,
 0.03797;-0.05281;-0.00582;,
 0.12689;-0.05282;0.16673;,
 0.41943;-0.05282;0.32325;,
 0.19524;0.14736;-0.17447;,
 0.44706;0.13735;-0.32601;,
 0.12689;0.15198;-0.00582;,
 0.19524;0.14736;0.16284;,
 0.44706;0.13735;0.31437;,
 0.44706;0.32724;-0.16603;,
 0.53901;0.29214;-0.29643;,
 0.41943;0.33777;-0.00582;,
 0.44706;0.32724;0.15439;,
 0.53901;0.29214;0.28480;,
 0.53901;-0.39777;0.28480;,
 0.94449;-0.43287;0.31437;,
 0.91825;-0.25300;0.39535;,
 0.44706;-0.24298;0.31437;,
 1.44268;-0.44341;0.32325;,
 1.44268;-0.25762;0.41733;,
 1.94086;-0.43287;0.31437;,
 1.96711;-0.25300;0.39535;,
 2.34635;-0.39777;0.28480;,
 2.43829;-0.24298;0.31437;,
 0.90616;-0.05282;0.41733;,
 0.41943;-0.05282;0.32325;,
 1.44268;-0.05281;0.44592;,
 1.97920;-0.05282;0.41733;,
 2.46593;-0.05282;0.32325;,
 0.91825;0.14736;0.39535;,
 0.44706;0.13735;0.31437;,
 1.44268;0.15198;0.41733;,
 1.96711;0.14736;0.39535;,
 2.43829;0.13735;0.31437;,
 0.94449;0.32724;0.31437;,
 0.53901;0.29214;0.28480;,
 1.44268;0.33777;0.32325;,
 1.94086;0.32724;0.31437;,
 2.34635;0.29214;0.28480;,
 2.34635;-0.39777;0.28480;,
 2.43829;-0.43287;0.15439;,
 2.69011;-0.25300;0.16284;,
 2.43829;-0.24298;0.31437;,
 2.46593;-0.44341;-0.00582;,
 2.75848;-0.25762;-0.00582;,
 2.43829;-0.43287;-0.16603;,
 2.69011;-0.25300;-0.17447;,
 2.34635;-0.39777;-0.29643;,
 2.43829;-0.24298;-0.32601;,
 2.75848;-0.05282;0.16673;,
 2.46593;-0.05282;0.32325;,
 2.84738;-0.05281;-0.00582;,
 2.75848;-0.05282;-0.17836;,
 2.46593;-0.05282;-0.33489;,
 2.69011;0.14736;0.16284;,
 2.43829;0.13735;0.31437;,
 2.75848;0.15198;-0.00582;,
 2.69011;0.14736;-0.17447;,
 2.43829;0.13735;-0.32601;,
 2.43829;0.32724;0.15439;,
 2.34635;0.29214;0.28480;,
 2.46593;0.33777;-0.00582;,
 2.43829;0.32724;-0.16603;,
 2.34635;0.29214;-0.29643;,
 1.94086;-0.43287;0.31437;,
 1.96711;-0.52899;0.16284;,
 2.43829;-0.43287;0.15439;,
 1.44268;-0.55508;0.16673;,
 0.94449;-0.43287;0.31437;,
 0.91825;-0.52899;0.16284;,
 0.44706;-0.43287;0.15439;,
 1.97920;-0.55508;-0.00582;,
 2.46593;-0.44341;-0.00582;,
 1.44268;-0.58902;-0.00582;,
 0.90616;-0.55508;-0.00582;,
 0.41943;-0.44341;-0.00582;,
 1.96711;-0.52899;-0.17447;,
 2.43829;-0.43287;-0.16603;,
 1.44268;-0.55508;-0.17836;,
 0.91825;-0.52899;-0.17447;,
 0.44706;-0.43287;-0.16603;,
 1.94086;-0.43287;-0.32601;,
 2.34635;-0.39777;-0.29643;,
 1.44268;-0.44341;-0.33489;,
 0.94449;-0.43287;-0.32601;,
 0.53901;-0.39777;-0.29643;,
 2.34635;0.29214;-0.29643;,
 1.94086;0.32724;-0.32601;,
 1.96711;0.42335;-0.17447;,
 2.43829;0.32724;-0.16603;,
 1.44268;0.33777;-0.33489;,
 1.44268;0.44944;-0.17836;,
 0.94449;0.32724;-0.32601;,
 0.91825;0.42335;-0.17447;,
 0.53901;0.29214;-0.29643;,
 0.44706;0.32724;-0.16603;,
 1.97920;0.44944;-0.00582;,
 2.46593;0.33777;-0.00582;,
 1.44268;0.48339;-0.00582;,
 0.90616;0.44944;-0.00582;,
 0.41943;0.33777;-0.00582;,
 1.96711;0.42335;0.16284;,
 2.43829;0.32724;0.15439;,
 1.44268;0.44944;0.16673;,
 0.91825;0.42335;0.16284;,
 0.44706;0.32724;0.15439;,
 1.94086;0.32724;0.31437;,
 0.94449;0.32724;0.31437;;
 
 96;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;3,2,10,11;,
 4;2,5,12,10;,
 4;5,7,13,12;,
 4;7,9,14,13;,
 4;11,10,15,16;,
 4;10,12,17,15;,
 4;12,13,18,17;,
 4;13,14,19,18;,
 4;16,15,20,21;,
 4;15,17,22,20;,
 4;17,18,23,22;,
 4;18,19,24,23;,
 4;25,26,27,28;,
 4;26,29,30,27;,
 4;29,31,32,30;,
 4;31,33,34,32;,
 4;28,27,35,36;,
 4;27,30,37,35;,
 4;30,32,38,37;,
 4;32,34,39,38;,
 4;36,35,40,41;,
 4;35,37,42,40;,
 4;37,38,43,42;,
 4;38,39,44,43;,
 4;41,40,45,46;,
 4;40,42,47,45;,
 4;42,43,48,47;,
 4;43,44,49,48;,
 4;50,51,52,53;,
 4;51,54,55,52;,
 4;54,56,57,55;,
 4;56,58,59,57;,
 4;53,52,60,61;,
 4;52,55,62,60;,
 4;55,57,63,62;,
 4;57,59,64,63;,
 4;61,60,65,66;,
 4;60,62,67,65;,
 4;62,63,68,67;,
 4;63,64,69,68;,
 4;66,65,70,71;,
 4;65,67,72,70;,
 4;67,68,73,72;,
 4;68,69,74,73;,
 4;75,76,77,78;,
 4;76,79,80,77;,
 4;79,81,82,80;,
 4;81,83,84,82;,
 4;78,77,85,86;,
 4;77,80,87,85;,
 4;80,82,88,87;,
 4;82,84,89,88;,
 4;86,85,90,91;,
 4;85,87,92,90;,
 4;87,88,93,92;,
 4;88,89,94,93;,
 4;91,90,95,96;,
 4;90,92,97,95;,
 4;92,93,98,97;,
 4;93,94,99,98;,
 4;75,100,101,102;,
 4;100,54,103,101;,
 4;54,104,105,103;,
 4;104,33,106,105;,
 4;102,101,107,108;,
 4;101,103,109,107;,
 4;103,105,110,109;,
 4;105,106,111,110;,
 4;108,107,112,113;,
 4;107,109,114,112;,
 4;109,110,115,114;,
 4;110,111,116,115;,
 4;113,112,117,118;,
 4;112,114,119,117;,
 4;114,115,120,119;,
 4;115,116,121,120;,
 4;122,123,124,125;,
 4;123,126,127,124;,
 4;126,128,129,127;,
 4;128,130,131,129;,
 4;125,124,132,133;,
 4;124,127,134,132;,
 4;127,129,135,134;,
 4;129,131,136,135;,
 4;133,132,137,138;,
 4;132,134,139,137;,
 4;134,135,140,139;,
 4;135,136,141,140;,
 4;138,137,142,96;,
 4;137,139,72,142;,
 4;139,140,143,72;,
 4;140,141,49,143;;
 
 MeshMaterialList {
  10;
  96;
  5,
  3,
  3,
  3,
  5,
  3,
  3,
  3,
  5,
  3,
  3,
  3,
  5,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  5,
  3,
  3,
  3,
  5,
  3,
  3,
  3,
  5,
  3,
  3,
  3,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  3,
  3,
  3,
  5,
  3,
  3,
  3,
  5,
  3,
  3,
  3,
  5,
  3,
  3,
  3,
  5,
  3,
  3,
  3,
  5,
  3,
  3,
  3,
  5,
  3,
  3,
  3,
  5,
  3,
  3,
  3;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Player/body.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Player/thight.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Player/glove.jpg";
   }
  }
  Material {
   0.360800;0.458400;0.501600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.272800;0.344800;0.380000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.235200;0.235200;0.235200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.228800;0.150400;0.044000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.021600;0.021600;0.021600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.680800;0.520800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.558400;0.395200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  98;
  0.288376;-0.627687;-0.723083;,
  0.094319;-0.653922;-0.750659;,
  0.000000;-0.653196;-0.757189;,
  -0.094318;-0.653922;-0.750659;,
  -0.288368;-0.627688;-0.723085;,
  0.346097;-0.296934;-0.889970;,
  0.100591;-0.254824;-0.961741;,
  0.000000;-0.283263;-0.959042;,
  -0.100590;-0.254823;-0.961741;,
  -0.346096;-0.296929;-0.889972;,
  0.340773;-0.000001;-0.940146;,
  0.114864;0.000001;-0.993381;,
  0.000000;0.000004;-1.000000;,
  -0.114863;0.000001;-0.993381;,
  -0.340780;-0.000001;-0.940143;,
  0.346099;0.296929;-0.889971;,
  0.100589;0.254820;-0.961743;,
  0.000000;0.283261;-0.959043;,
  -0.100588;0.254819;-0.961743;,
  -0.346098;0.296925;-0.889973;,
  0.288377;0.627692;-0.723078;,
  0.094313;0.653929;-0.750654;,
  0.000000;0.653201;-0.757185;,
  -0.094312;0.653929;-0.750654;,
  -0.288369;0.627693;-0.723080;,
  -0.378555;-0.844095;-0.379736;,
  -0.391320;-0.920255;-0.000003;,
  -0.378558;-0.844095;0.379733;,
  -0.288372;-0.627686;0.723085;,
  -0.653968;-0.498633;-0.568939;,
  -0.773514;-0.633779;-0.000007;,
  -0.653969;-0.498634;0.568937;,
  -0.346096;-0.296920;0.889975;,
  -0.729687;0.000003;-0.683782;,
  -1.000000;0.000008;-0.000011;,
  -0.729684;0.000003;0.683784;,
  -0.340771;-0.000001;0.940146;,
  -0.653971;0.498633;-0.568934;,
  -0.773512;0.633781;-0.000007;,
  -0.653972;0.498634;0.568932;,
  -0.346098;0.296916;0.889976;,
  -0.378558;0.844103;-0.379716;,
  -0.391322;0.920254;-0.000003;,
  -0.378561;0.844103;0.379713;,
  -0.288372;0.627691;0.723081;,
  -0.094315;-0.653920;0.750662;,
  0.000000;-0.653193;0.757192;,
  0.094316;-0.653920;0.750662;,
  0.288380;-0.627685;0.723083;,
  -0.100589;-0.254816;0.961744;,
  0.000000;-0.283262;0.959043;,
  0.100590;-0.254817;0.961743;,
  0.346097;-0.296925;0.889973;,
  -0.114864;0.000001;0.993381;,
  0.000000;0.000003;1.000000;,
  0.114864;0.000001;0.993381;,
  0.340764;-0.000001;0.940149;,
  -0.100587;0.254812;0.961745;,
  0.000000;0.283260;0.959043;,
  0.100588;0.254813;0.961745;,
  0.346099;0.296920;0.889974;,
  -0.094309;0.653927;0.750657;,
  0.000000;0.653198;0.757187;,
  0.094310;0.653927;0.750657;,
  0.288380;0.627690;0.723079;,
  0.378558;-0.844093;0.379739;,
  0.391312;-0.920258;-0.000003;,
  0.378555;-0.844092;-0.379742;,
  0.653961;-0.498638;0.568942;,
  0.773508;-0.633786;-0.000007;,
  0.653960;-0.498636;-0.568944;,
  0.729678;0.000003;0.683791;,
  1.000000;0.000008;-0.000011;,
  0.729680;0.000003;-0.683788;,
  0.653965;0.498638;0.568938;,
  0.773506;0.633789;-0.000007;,
  0.653964;0.498637;-0.568940;,
  0.378561;0.844100;0.379719;,
  0.391314;0.920257;-0.000003;,
  0.378558;0.844100;-0.379722;,
  0.116697;-0.932884;0.340749;,
  0.000000;-0.926402;0.376536;,
  -0.116696;-0.932884;0.340747;,
  0.135876;-0.990726;-0.000004;,
  -0.000000;-1.000000;-0.000005;,
  -0.135875;-0.990726;-0.000004;,
  0.116697;-0.932885;-0.340744;,
  0.000000;-0.926406;-0.376527;,
  -0.116696;-0.932886;-0.340743;,
  0.116692;0.932890;-0.340732;,
  0.000000;0.926405;-0.376530;,
  -0.116691;0.932891;-0.340730;,
  0.135876;0.990726;-0.000004;,
  -0.000000;1.000000;-0.000005;,
  -0.135875;0.990726;-0.000004;,
  0.116692;0.932889;0.340736;,
  0.000000;0.926401;0.376539;,
  -0.116692;0.932890;0.340735;;
  96;
  4;0,1,6,5;,
  4;1,2,7,6;,
  4;2,3,8,7;,
  4;3,4,9,8;,
  4;5,6,11,10;,
  4;6,7,12,11;,
  4;7,8,13,12;,
  4;8,9,14,13;,
  4;10,11,16,15;,
  4;11,12,17,16;,
  4;12,13,18,17;,
  4;13,14,19,18;,
  4;15,16,21,20;,
  4;16,17,22,21;,
  4;17,18,23,22;,
  4;18,19,24,23;,
  4;4,25,29,9;,
  4;25,26,30,29;,
  4;26,27,31,30;,
  4;27,28,32,31;,
  4;9,29,33,14;,
  4;29,30,34,33;,
  4;30,31,35,34;,
  4;31,32,36,35;,
  4;14,33,37,19;,
  4;33,34,38,37;,
  4;34,35,39,38;,
  4;35,36,40,39;,
  4;19,37,41,24;,
  4;37,38,42,41;,
  4;38,39,43,42;,
  4;39,40,44,43;,
  4;28,45,49,32;,
  4;45,46,50,49;,
  4;46,47,51,50;,
  4;47,48,52,51;,
  4;32,49,53,36;,
  4;49,50,54,53;,
  4;50,51,55,54;,
  4;51,52,56,55;,
  4;36,53,57,40;,
  4;53,54,58,57;,
  4;54,55,59,58;,
  4;55,56,60,59;,
  4;40,57,61,44;,
  4;57,58,62,61;,
  4;58,59,63,62;,
  4;59,60,64,63;,
  4;48,65,68,52;,
  4;65,66,69,68;,
  4;66,67,70,69;,
  4;67,0,5,70;,
  4;52,68,71,56;,
  4;68,69,72,71;,
  4;69,70,73,72;,
  4;70,5,10,73;,
  4;56,71,74,60;,
  4;71,72,75,74;,
  4;72,73,76,75;,
  4;73,10,15,76;,
  4;60,74,77,64;,
  4;74,75,78,77;,
  4;75,76,79,78;,
  4;76,15,20,79;,
  4;48,47,80,65;,
  4;47,46,81,80;,
  4;46,45,82,81;,
  4;45,28,27,82;,
  4;65,80,83,66;,
  4;80,81,84,83;,
  4;81,82,85,84;,
  4;82,27,26,85;,
  4;66,83,86,67;,
  4;83,84,87,86;,
  4;84,85,88,87;,
  4;85,26,25,88;,
  4;67,86,1,0;,
  4;86,87,2,1;,
  4;87,88,3,2;,
  4;88,25,4,3;,
  4;20,21,89,79;,
  4;21,22,90,89;,
  4;22,23,91,90;,
  4;23,24,41,91;,
  4;79,89,92,78;,
  4;89,90,93,92;,
  4;90,91,94,93;,
  4;91,41,42,94;,
  4;78,92,95,77;,
  4;92,93,96,95;,
  4;93,94,97,96;,
  4;94,42,43,97;,
  4;77,95,63,64;,
  4;95,96,62,63;,
  4;96,97,61,62;,
  4;97,43,44,61;;
 }
 MeshTextureCoords {
  144;
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.250000;1.000000;,
  0.750000;1.000000;;
 }
}