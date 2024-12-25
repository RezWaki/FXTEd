#include "fxtfile.h"
#include <Windows.h>
#include <stdio.h>
#include <msclr\marshal.h>

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace msclr::interop;

String^ LoadFXT( String^ filename ) {
	FILE* pFXTFile;
	BYTE bByte;
	INT filesize;
	String^ txt;
	INT iMask[8] = { 100, 199, 141, 25, 49, 97, -63, 129 };

	bByte = 0;
	pFXTFile = fopen( (char*)Marshal::StringToHGlobalAnsi(filename).ToPointer(), "rb" );
	fseek( pFXTFile, 0, SEEK_END );
	filesize = ftell( pFXTFile );
	fseek( pFXTFile, 0, SEEK_SET );

	for( INT i = 0; i < filesize; i++ ) {
		fread( &bByte, 1, 1, pFXTFile );
		if( i < 8 ) bByte -= iMask[i];
		else bByte--;
		if( bByte == 0x00 ) bByte = '\n';
		txt += (wchar_t)bByte;
	}

	fclose( pFXTFile );

	return txt;
}

void SaveFXT( System::String^ filename, System::String^ text ) {
	FILE* pFXTFile;
	BYTE bByte;
	INT iMask[8] = { 100, 199, 141, 25, 49, 97, -63, 129 };

	bByte = 0;
	pFXTFile = fopen( (char*)Marshal::StringToHGlobalAnsi(filename).ToPointer(), "wb" );
	if( !pFXTFile ) return;

	for( INT i = 0; i < text->Length; i++ ) {
		if( i < 8 ) bByte = text[i]+iMask[i];
		else bByte = text[i]+1;
		if( bByte == 0x0B ) bByte = 0x01;
		fwrite( &bByte, 1, 1, pFXTFile );
	}

	fclose( pFXTFile );
}