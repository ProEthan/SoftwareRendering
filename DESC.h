#pragma once

typedef struct INPUT_ELEMENT_DESC {
	string SemanticName;
	UINT vertexSize;
}INPUT_ELEMENT_DESC;

typedef struct BUFFER_DESC {
	UINT ByteWidth;
}BUFFER_DESC;

typedef struct SUBRESOURCE_DATA {
	float* pSysMem;
	UINT SysMemPitch;
	UINT SysMemSlicePitch;
}SUBRESOURCE_DATA;