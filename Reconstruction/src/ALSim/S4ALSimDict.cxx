// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME S4ALSimDict
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
#include "MakeRawBPDEvent_503f.h"
#include "MakeRawEventMC.h"
#include "MakeEventData.h"
#include "ALEvent.h"
#include "LoadMCparameters.h"
#include "LoadDataparameters.h"
#include "ALTckhit.h"
#include "../../tools.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_ALTckhit(void *p = 0);
   static void *newArray_ALTckhit(Long_t size, void *p);
   static void delete_ALTckhit(void *p);
   static void deleteArray_ALTckhit(void *p);
   static void destruct_ALTckhit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ALTckhit*)
   {
      ::ALTckhit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::ALTckhit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("ALTckhit", ::ALTckhit::Class_Version(), "ALTckhit.h", 16,
                  typeid(::ALTckhit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::ALTckhit::Dictionary, isa_proxy, 4,
                  sizeof(::ALTckhit) );
      instance.SetNew(&new_ALTckhit);
      instance.SetNewArray(&newArray_ALTckhit);
      instance.SetDelete(&delete_ALTckhit);
      instance.SetDeleteArray(&deleteArray_ALTckhit);
      instance.SetDestructor(&destruct_ALTckhit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ALTckhit*)
   {
      return GenerateInitInstanceLocal((::ALTckhit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::ALTckhit*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_ALEvent(void *p = 0);
   static void *newArray_ALEvent(Long_t size, void *p);
   static void delete_ALEvent(void *p);
   static void deleteArray_ALEvent(void *p);
   static void destruct_ALEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ALEvent*)
   {
      ::ALEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::ALEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("ALEvent", ::ALEvent::Class_Version(), "ALEvent.h", 14,
                  typeid(::ALEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::ALEvent::Dictionary, isa_proxy, 4,
                  sizeof(::ALEvent) );
      instance.SetNew(&new_ALEvent);
      instance.SetNewArray(&newArray_ALEvent);
      instance.SetDelete(&delete_ALEvent);
      instance.SetDeleteArray(&deleteArray_ALEvent);
      instance.SetDestructor(&destruct_ALEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ALEvent*)
   {
      return GenerateInitInstanceLocal((::ALEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::ALEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr ALTckhit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *ALTckhit::Class_Name()
{
   return "ALTckhit";
}

//______________________________________________________________________________
const char *ALTckhit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ALTckhit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int ALTckhit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ALTckhit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *ALTckhit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ALTckhit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *ALTckhit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ALTckhit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr ALEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *ALEvent::Class_Name()
{
   return "ALEvent";
}

//______________________________________________________________________________
const char *ALEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ALEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int ALEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ALEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *ALEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ALEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *ALEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ALEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void ALTckhit::Streamer(TBuffer &R__b)
{
   // Stream an object of class ALTckhit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(ALTckhit::Class(),this);
   } else {
      R__b.WriteClassBuffer(ALTckhit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_ALTckhit(void *p) {
      return  p ? new(p) ::ALTckhit : new ::ALTckhit;
   }
   static void *newArray_ALTckhit(Long_t nElements, void *p) {
      return p ? new(p) ::ALTckhit[nElements] : new ::ALTckhit[nElements];
   }
   // Wrapper around operator delete
   static void delete_ALTckhit(void *p) {
      delete ((::ALTckhit*)p);
   }
   static void deleteArray_ALTckhit(void *p) {
      delete [] ((::ALTckhit*)p);
   }
   static void destruct_ALTckhit(void *p) {
      typedef ::ALTckhit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::ALTckhit

//______________________________________________________________________________
void ALEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class ALEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(ALEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(ALEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_ALEvent(void *p) {
      return  p ? new(p) ::ALEvent : new ::ALEvent;
   }
   static void *newArray_ALEvent(Long_t nElements, void *p) {
      return p ? new(p) ::ALEvent[nElements] : new ::ALEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_ALEvent(void *p) {
      delete ((::ALEvent*)p);
   }
   static void deleteArray_ALEvent(void *p) {
      delete [] ((::ALEvent*)p);
   }
   static void destruct_ALEvent(void *p) {
      typedef ::ALEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::ALEvent

namespace ROOT {
   static TClass *vectorlEfloatgR_Dictionary();
   static void vectorlEfloatgR_TClassManip(TClass*);
   static void *new_vectorlEfloatgR(void *p = 0);
   static void *newArray_vectorlEfloatgR(Long_t size, void *p);
   static void delete_vectorlEfloatgR(void *p);
   static void deleteArray_vectorlEfloatgR(void *p);
   static void destruct_vectorlEfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<float>*)
   {
      vector<float> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<float>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<float>", -2, "vector", 386,
                  typeid(vector<float>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEfloatgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<float>) );
      instance.SetNew(&new_vectorlEfloatgR);
      instance.SetNewArray(&newArray_vectorlEfloatgR);
      instance.SetDelete(&delete_vectorlEfloatgR);
      instance.SetDeleteArray(&deleteArray_vectorlEfloatgR);
      instance.SetDestructor(&destruct_vectorlEfloatgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<float> >()));

      ::ROOT::AddClassAlternate("vector<float>","std::vector<float, std::allocator<float> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<float>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<float>*)0x0)->GetClass();
      vectorlEfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEfloatgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float> : new vector<float>;
   }
   static void *newArray_vectorlEfloatgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float>[nElements] : new vector<float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEfloatgR(void *p) {
      delete ((vector<float>*)p);
   }
   static void deleteArray_vectorlEfloatgR(void *p) {
      delete [] ((vector<float>*)p);
   }
   static void destruct_vectorlEfloatgR(void *p) {
      typedef vector<float> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<float>

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 386,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));

      ::ROOT::AddClassAlternate("vector<double>","std::vector<double, std::allocator<double> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace ROOT {
   static TClass *vectorlEALTckhitmUgR_Dictionary();
   static void vectorlEALTckhitmUgR_TClassManip(TClass*);
   static void *new_vectorlEALTckhitmUgR(void *p = 0);
   static void *newArray_vectorlEALTckhitmUgR(Long_t size, void *p);
   static void delete_vectorlEALTckhitmUgR(void *p);
   static void deleteArray_vectorlEALTckhitmUgR(void *p);
   static void destruct_vectorlEALTckhitmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<ALTckhit*>*)
   {
      vector<ALTckhit*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<ALTckhit*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<ALTckhit*>", -2, "vector", 386,
                  typeid(vector<ALTckhit*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEALTckhitmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<ALTckhit*>) );
      instance.SetNew(&new_vectorlEALTckhitmUgR);
      instance.SetNewArray(&newArray_vectorlEALTckhitmUgR);
      instance.SetDelete(&delete_vectorlEALTckhitmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEALTckhitmUgR);
      instance.SetDestructor(&destruct_vectorlEALTckhitmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<ALTckhit*> >()));

      ::ROOT::AddClassAlternate("vector<ALTckhit*>","std::vector<ALTckhit*, std::allocator<ALTckhit*> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<ALTckhit*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEALTckhitmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<ALTckhit*>*)0x0)->GetClass();
      vectorlEALTckhitmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEALTckhitmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEALTckhitmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<ALTckhit*> : new vector<ALTckhit*>;
   }
   static void *newArray_vectorlEALTckhitmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<ALTckhit*>[nElements] : new vector<ALTckhit*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEALTckhitmUgR(void *p) {
      delete ((vector<ALTckhit*>*)p);
   }
   static void deleteArray_vectorlEALTckhitmUgR(void *p) {
      delete [] ((vector<ALTckhit*>*)p);
   }
   static void destruct_vectorlEALTckhitmUgR(void *p) {
      typedef vector<ALTckhit*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<ALTckhit*>

namespace {
  void TriggerDictionaryInitialization_S4ALSimDict_Impl() {
    static const char* headers[] = {
"MakeRawBPDEvent_503f.h",
"MakeRawEventMC.h",
"MakeEventData.h",
"ALEvent.h",
"LoadMCparameters.h",
"LoadDataparameters.h",
"ALTckhit.h",
"../../tools.h",
0
    };
    static const char* includePaths[] = {
"../../include",
"/home/psmangeard/Programs/ROOT/root/include/",
"/media/psmangeard/DATA/Documents/UDEL/AESOPLITE2/AL2/Reconstruction/src/ALSim/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "S4ALSimDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$ALTckhit.h")))  __attribute__((annotate("$clingAutoload$MakeRawBPDEvent_503f.h")))  ALTckhit;
class __attribute__((annotate("$clingAutoload$ALEvent.h")))  __attribute__((annotate("$clingAutoload$MakeRawBPDEvent_503f.h")))  ALEvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "S4ALSimDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "MakeRawBPDEvent_503f.h"
#include "MakeRawEventMC.h"
#include "MakeEventData.h"
#include "ALEvent.h"
#include "LoadMCparameters.h"
#include "LoadDataparameters.h"
#include "ALTckhit.h"
#include "../../tools.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"ALEvent", payloadCode, "@",
"ALTckhit", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("S4ALSimDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_S4ALSimDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_S4ALSimDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_S4ALSimDict() {
  TriggerDictionaryInitialization_S4ALSimDict_Impl();
}
