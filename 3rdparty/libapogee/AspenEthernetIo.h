/*! 
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
*
* Copyright(c) 2009 Apogee Instruments, Inc. 
* \class AspenEthernetIo 
* \brief Class for talking with apsen generation cameras with libcurl 
* 
*/ 


#ifndef ASPENETHERNETIO_INCLUDE_H__ 
#define ASPENETHERNETIO_INCLUDE_H__ 


#include "ICamIo.h" 
#include <string>
#include <vector>

#ifdef WIN_OS
#include <memory>
#else
#include <tr1/memory>
#endif

class CLibCurlWrap;

class AspenEthernetIo : public ICamIo
{ 
    public: 
        AspenEthernetIo( const std::string url );
        virtual ~AspenEthernetIo(); 


        uint16_t ReadReg( uint16_t reg ) const;
	    void WriteReg( uint16_t reg, uint16_t val ) ;

        void GetImageData( std::vector<uint16_t> & data );

        void SetupImgXfer(uint16_t Rows, 
            uint16_t Cols,
            uint16_t NumOfImages, bool IsBulkSeq);

        void CancelImgXfer();

        void GetStatus(CameraStatusRegs::AdvStatus & status);
        void GetStatus(CameraStatusRegs::BasicStatus & status);

        //Functions unique to the second generation of the 
        //ethernet interface
        uint8_t ReadRegBufCon(uint16_t Reg);
        void WriteRegBufCon(uint16_t Reg, uint8_t & Val);

        uint8_t ReadRegPhy(uint16_t Reg);
        void WriteConPhy(uint16_t Reg, uint8_t & Val);

        void GetMacAddress( std::string & Mac );

        void WriteSRMD( uint16_t reg, const std::vector<uint16_t> & data );

        void WriteMRMD( uint16_t reg, const std::vector<uint16_t> & data );

        std::string GetNetworkSettings();

        std::string GetDriverVersion();

        uint16_t GetFirmwareRev();
        std::string GetInfo();

        std::vector<std::string> ReadStrDatabase();

        // TODO - see if we can do same error
        // trapping we do in USB
        bool IsError() { return false; }

    private:
        const std::string m_url;
        const std::string m_fileName;
        std::string m_sessionKey;
        std::string m_sessionKeyUrlStr;

		unsigned int getLastExposureTime();
		uint16_t m_lastExposureTimeRegHigh;
		uint16_t m_lastExposureTimeRegLow;

        void StartSession();
        void EndSession();
        bool ReadStrDatabase( const uint32_t offset, const uint32_t size2Read, 
                                      std::vector<uint8_t> & out );

        std::tr1::shared_ptr<CLibCurlWrap> m_libcurl;
        //disable the copy ctor and assignment operator
        //generated by the compiler
        //Effective C++ Item 6
        AspenEthernetIo(const AspenEthernetIo&);
        AspenEthernetIo& operator=(AspenEthernetIo&);
}; 

#endif
