// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME S4ALPatternRecoDict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "ALPatternRecognition.h"
#include "../../tools.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_ALPatternRecognition(void *p = 0);
   static void *newArray_ALPatternRecognition(Long_t size, void *p);
   static void delete_ALPatternRecognition(void *p);
   static void deleteArray_ALPatternRecognition(void *p);
   static void destruct_ALPatternRecognition(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ALPatternRecognition*)
   {
      ::ALPatternRecognition *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::ALPatternRecognition >(0);
      static ::ROOT::TGenericClassInfo 
         instance("ALPatternRecognition", ::ALPatternRecognition::Class_Version(), "ALPatternRecognition.h", 73,
                  typeid(::ALPatternRecognition), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::ALPatternRecognition::Dictionary, isa_proxy, 4,
                  sizeof(::ALPatternRecognition) );
      instance.SetNew(&new_ALPatternRecognition);
      instance.SetNewArray(&newArray_ALPatternRecognition);
      instance.SetDelete(&delete_ALPatternRecognition);
      instance.SetDeleteArray(&deleteArray_ALPatternRecognition);
      instance.SetDestructor(&destruct_ALPatternRecognition);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ALPatternRecognition*)
   {
      return GenerateInitInstanceLocal((::ALPatternRecognition*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::ALPatternRecognition*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr ALPatternRecognition::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *ALPatternRecognition::Class_Name()
{
   return "ALPatternRecognition";
}

//______________________________________________________________________________
const char *ALPatternRecognition::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ALPatternRecognition*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int ALPatternRecognition::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ALPatternRecognition*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *ALPatternRecognition::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ALPatternRecognition*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *ALPatternRecognition::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ALPatternRecognition*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void ALPatternRecognition::Streamer(TBuffer &R__b)
{
   // Stream an object of class ALPatternRecognition.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(ALPatternRecognition::Class(),this);
   } else {
      R__b.WriteClassBuffer(ALPatternRecognition::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_ALPatternRecognition(void *p) {
      return  p ? new(p) ::ALPatternRecognition : new ::ALPatternRecognition;
   }
   static void *newArray_ALPatternRecognition(Long_t nElements, void *p) {
      return p ? new(p) ::ALPatternRecognition[nElements] : new ::ALPatternRecognition[nElements];
   }
   // Wrapper around operator delete
   static void delete_ALPatternRecognition(void *p) {
      delete ((::ALPatternRecognition*)p);
   }
   static void deleteArray_ALPatternRecognition(void *p) {
      delete [] ((::ALPatternRecognition*)p);
   }
   static void destruct_ALPatternRecognition(void *p) {
      typedef ::ALPatternRecognition current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::ALPatternRecognition

namespace {
  void TriggerDictionaryInitialization_S4ALPatternRecoDict_Impl() {
    static const char* headers[] = {
"ALPatternRecognition.h",
"../../tools.h",
0
    };
    static const char* includePaths[] = {
"../../include",
"/home/psmangeard/Programs/ROOT/root/include/",
"/media/psmangeard/DATA/Documents/UDEL/AESOPLITE2/AL2/Reconstruction/src/ALPatternRecognition/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "S4ALPatternRecoDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$ALPatternRecognition.h")))  ALPatternRecognition;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "S4ALPatternRecoDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "ALPatternRecognition.h"
#include "../../tools.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"ALPatternRecognition", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("S4ALPatternRecoDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_S4ALPatternRecoDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_S4ALPatternRecoDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_S4ALPatternRecoDict() {
  TriggerDictionaryInitialization_S4ALPatternRecoDict_Impl();
}
