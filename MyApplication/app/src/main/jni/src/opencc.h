/*
 * Open Chinese Convert
 *
 * Copyright 2010-2014 BYVoid <byvoid@byvoid.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifdef __cplusplus
#include <string>
#include "Export.hpp"
extern "C" {
#endif

/**
* @defgroup opencc_c_api OpenCC C API
*
* API in C language
*/

/**
* Type of opencc descriptor
*
* @ingroup opencc_c_api
*/
typedef void* opencc_t;

/**
* Makes an instance of opencc
*
* @param configFileName Location of configuration file. If this is set to NULL,
*                       OPENCC_DEFAULT_CONFIG_SIMP_TO_TRAD will be loaded.
* @return            A description pointer of the newly allocated instance of
*                    opencc. On error the return value will be (opencc_t) -1.
* @ingroup opencc_c_api
*/
 opencc_t opencc_open(const char* configFileName);

/**
* Destroys an instance of opencc
*
* @param opencc The description pointer.
* @return 0 on success or non-zero number on failure.
* @ingroup opencc_c_api
*/

int opencc_close(opencc_t opencc);

/**
* Converts UTF-8 string
*
* @param opencc The opencc description pointer.
* @param input  The UTF-8 encoded string.
* @param length The maximum length in byte to convert. If length is (size_t)-1,
*               the whole string (terminated by '\0') will be converted.
* @param output The buffer to store converted text. You MUST make sure this
*               buffer has sufficient space.
*
* @return       The length of converted string or (size_t)-1 on error.
*
* @ingroup opencc_c_api
*/
 size_t opencc_convert_utf8_to_buffer(opencc_t opencc,
const char* input,
        size_t length,
char* output);

/**
* Converts UTF-8 string
* This function returns an allocated C-Style string, which stores
* the converted string.
* You MUST call opencc_convert_utf8_free() to release allocated memory.
*
* @param opencc The opencc description pointer.
* @param input  The UTF-8 encoded string.
* @param length The maximum length in byte to convert. If length is (size_t)-1,
*               the whole string (terminated by '\0') will be converted.
*
* @return       The newly allocated UTF-8 string that stores text converted,
*               or NULL on error.
* @ingroup opencc_c_api
*/
 char* opencc_convert_utf8(opencc_t opencc,
                                        const char* input,
                                        size_t length);

/**
* Releases allocated buffer by opencc_convert_utf8
*
* @param str    Pointer to the allocated string buffer by opencc_convert_utf8.
*
* @ingroup opencc_c_api
*/
 void opencc_convert_utf8_free(char* str);

/**
* Returns the last error message
*
* Note that this function is the only one which is NOT thread-safe.
*
* @ingroup opencc_c_api
*/
 const char* opencc_error(void);
#ifdef __cplusplus
}
#endif

/**
* @defgroup opencc_simple_api OpenCC C++ Simple API
*
* Simple API in C++ language
*/

#ifdef __cplusplus

namespace opencc {

/**
* A high level converter
* This interface does not require C++11 to compile.
* @ingroup opencc_simple_api
*/
  class SimpleConverter {
    public:
    /**
    * Constructor of SimpleConverter
    * @param configFileName File name of configuration.
    */
    SimpleConverter(const std::string& configFileName);

    ~SimpleConverter();

    /**
    * Converts a text
    * @param input Text to be converted.
    */
    std::string Convert(const std::string& input) const;

    /**
    * Converts a text
    * @param input A C-Style string (terminated by '\0') to be converted.
    */
    std::string Convert(const char* input) const;

    /**
    * Converts a text
    * @param input  A C-Style string limited by a given length to be converted.
    * @param length Maximal length in byte of the input string.
    */
    std::string Convert(const char* input, size_t length) const;

    /**
    * Converts a text and writes to an allocated buffer
    * Please make sure the buffer has sufficent space.
    * @param input  A C-Style string (terminated by '\0') to be converted.
    * @param output Buffer to write the converted text.
    * @return       Length of converted text.
    */
    size_t Convert(const char* input, char* output) const;

    /**
    * Converts a text and writes to an allocated buffer
    * Please make sure the buffer has sufficent space.
    * @param input  A C-Style string limited by a given length to be converted.
    * @param length Maximal length in byte of the input string.
    * @param output Buffer to write the converted text.
    * @return       Length of converted text.
    */
    size_t Convert(const char* input, size_t length, char* output) const;

    private:
    const void* internalData;
  };
}

#endif


/**
* @defgroup opencc_cpp_api OpenCC C++ Comprehensive API
*
* Comprehensive API in C++ language
*/

