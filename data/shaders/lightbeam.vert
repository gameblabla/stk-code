//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2013 the SuperTuxKart team
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 3
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.


// Jean-manuel clemencon (C) Copyright supertuxkart
// Creates a cone lightbeam effect by smoothing edges
#version 130
out vec2 uv;
noperspective out vec3 eyeVec;
noperspective out vec3 normal;

void main()
{
	vec4 viewp = gl_ModelViewMatrix * gl_Vertex;

	eyeVec = normalize(-viewp).xyz;
	normal = gl_NormalMatrix * gl_Normal;

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	uv = gl_MultiTexCoord0.st;
}
