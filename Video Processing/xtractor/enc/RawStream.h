/*
 * RawStream.h - Copyright (C) 2000 Jay A. Key
 *
 **********************************************************************
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */
#ifndef _RAWSTREAM_H_INC
#define _RAWSTREAM_H_INC

#include "encbase.h"

class RawStream : public BaseEncoderStream
{
 public:
  RawStream():BaseEncoderStream() { lstrcpy( _ext, "dat" ); lstrcpy( _mode, "wb" ); };
  virtual int SetOption( int opt, char *pszData );
  //virtual int OpenOutputFile( void );
  virtual unsigned int Encode( unsigned char *pData, unsigned int len );
};


#endif
