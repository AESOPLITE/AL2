// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME S4RKFitterDict
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
#include "RKfitter.h"
#include "FieldMap.h"
#include "Histogram.h"
#include "TkrData.h"
#include "RungeKutta4.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static TClass *TkrData_Dictionary();
   static void TkrData_TClassManip(TClass*);
   static void delete_TkrData(void *p);
   static void deleteArray_TkrData(void *p);
   static void destruct_TkrData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TkrData*)
   {
      ::TkrData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TkrData));
      static ::ROOT::TGenericClassInfo 
         instance("TkrData", "TkrData.h", 15,
                  typeid(::TkrData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &TkrData_Dictionary, isa_proxy, 4,
                  sizeof(::TkrData) );
      instance.SetDelete(&delete_TkrData);
      instance.SetDeleteArray(&deleteArray_TkrData);
      instance.SetDestructor(&destruct_TkrData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TkrData*)
   {
      return GenerateInitInstanceLocal((::TkrData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TkrData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TkrData_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TkrData*)0x0)->GetClass();
      TkrData_TClassManip(theClass);
   return theClass;
   }

   static void TkrData_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *FieldMap_Dictionary();
   static void FieldMap_TClassManip(TClass*);
   static void *new_FieldMap(void *p = 0);
   static void *newArray_FieldMap(Long_t size, void *p);
   static void delete_FieldMap(void *p);
   static void deleteArray_FieldMap(void *p);
   static void destruct_FieldMap(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FieldMap*)
   {
      ::FieldMap *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::FieldMap));
      static ::ROOT::TGenericClassInfo 
         instance("FieldMap", "FieldMap.h", 14,
                  typeid(::FieldMap), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &FieldMap_Dictionary, isa_proxy, 4,
                  sizeof(::FieldMap) );
      instance.SetNew(&new_FieldMap);
      instance.SetNewArray(&newArray_FieldMap);
      instance.SetDelete(&delete_FieldMap);
      instance.SetDeleteArray(&deleteArray_FieldMap);
      instance.SetDestructor(&destruct_FieldMap);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FieldMap*)
   {
      return GenerateInitInstanceLocal((::FieldMap*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FieldMap*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *FieldMap_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::FieldMap*)0x0)->GetClass();
      FieldMap_TClassManip(theClass);
   return theClass;
   }

   static void FieldMap_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *RungeKutta4_Dictionary();
   static void RungeKutta4_TClassManip(TClass*);
   static void delete_RungeKutta4(void *p);
   static void deleteArray_RungeKutta4(void *p);
   static void destruct_RungeKutta4(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RungeKutta4*)
   {
      ::RungeKutta4 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::RungeKutta4));
      static ::ROOT::TGenericClassInfo 
         instance("RungeKutta4", "RungeKutta4.h", 11,
                  typeid(::RungeKutta4), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RungeKutta4_Dictionary, isa_proxy, 4,
                  sizeof(::RungeKutta4) );
      instance.SetDelete(&delete_RungeKutta4);
      instance.SetDeleteArray(&deleteArray_RungeKutta4);
      instance.SetDestructor(&destruct_RungeKutta4);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RungeKutta4*)
   {
      return GenerateInitInstanceLocal((::RungeKutta4*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::RungeKutta4*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RungeKutta4_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::RungeKutta4*)0x0)->GetClass();
      RungeKutta4_TClassManip(theClass);
   return theClass;
   }

   static void RungeKutta4_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *RKfitter_Dictionary();
   static void RKfitter_TClassManip(TClass*);
   static void delete_RKfitter(void *p);
   static void deleteArray_RKfitter(void *p);
   static void destruct_RKfitter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RKfitter*)
   {
      ::RKfitter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::RKfitter));
      static ::ROOT::TGenericClassInfo 
         instance("RKfitter", "RKfitter.h", 35,
                  typeid(::RKfitter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RKfitter_Dictionary, isa_proxy, 4,
                  sizeof(::RKfitter) );
      instance.SetDelete(&delete_RKfitter);
      instance.SetDeleteArray(&deleteArray_RKfitter);
      instance.SetDestructor(&destruct_RKfitter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RKfitter*)
   {
      return GenerateInitInstanceLocal((::RKfitter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::RKfitter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RKfitter_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::RKfitter*)0x0)->GetClass();
      RKfitter_TClassManip(theClass);
   return theClass;
   }

   static void RKfitter_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Histogram_Dictionary();
   static void Histogram_TClassManip(TClass*);
   static void delete_Histogram(void *p);
   static void deleteArray_Histogram(void *p);
   static void destruct_Histogram(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Histogram*)
   {
      ::Histogram *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Histogram));
      static ::ROOT::TGenericClassInfo 
         instance("Histogram", "Histogram.h", 14,
                  typeid(::Histogram), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Histogram_Dictionary, isa_proxy, 4,
                  sizeof(::Histogram) );
      instance.SetDelete(&delete_Histogram);
      instance.SetDeleteArray(&deleteArray_Histogram);
      instance.SetDestructor(&destruct_Histogram);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Histogram*)
   {
      return GenerateInitInstanceLocal((::Histogram*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Histogram*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Histogram_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Histogram*)0x0)->GetClass();
      Histogram_TClassManip(theClass);
   return theClass;
   }

   static void Histogram_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrapper around operator delete
   static void delete_TkrData(void *p) {
      delete ((::TkrData*)p);
   }
   static void deleteArray_TkrData(void *p) {
      delete [] ((::TkrData*)p);
   }
   static void destruct_TkrData(void *p) {
      typedef ::TkrData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TkrData

namespace ROOT {
   // Wrappers around operator new
   static void *new_FieldMap(void *p) {
      return  p ? new(p) ::FieldMap : new ::FieldMap;
   }
   static void *newArray_FieldMap(Long_t nElements, void *p) {
      return p ? new(p) ::FieldMap[nElements] : new ::FieldMap[nElements];
   }
   // Wrapper around operator delete
   static void delete_FieldMap(void *p) {
      delete ((::FieldMap*)p);
   }
   static void deleteArray_FieldMap(void *p) {
      delete [] ((::FieldMap*)p);
   }
   static void destruct_FieldMap(void *p) {
      typedef ::FieldMap current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FieldMap

namespace ROOT {
   // Wrapper around operator delete
   static void delete_RungeKutta4(void *p) {
      delete ((::RungeKutta4*)p);
   }
   static void deleteArray_RungeKutta4(void *p) {
      delete [] ((::RungeKutta4*)p);
   }
   static void destruct_RungeKutta4(void *p) {
      typedef ::RungeKutta4 current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RungeKutta4

namespace ROOT {
   // Wrapper around operator delete
   static void delete_RKfitter(void *p) {
      delete ((::RKfitter*)p);
   }
   static void deleteArray_RKfitter(void *p) {
      delete [] ((::RKfitter*)p);
   }
   static void destruct_RKfitter(void *p) {
      typedef ::RKfitter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RKfitter

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Histogram(void *p) {
      delete ((::Histogram*)p);
   }
   static void deleteArray_Histogram(void *p) {
      delete [] ((::Histogram*)p);
   }
   static void destruct_Histogram(void *p) {
      typedef ::Histogram current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Histogram

namespace ROOT {
   static TClass *vectorlEvectorlEdoublegRsPgR_Dictionary();
   static void vectorlEvectorlEdoublegRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlEdoublegRsPgR(void *p = 0);
   static void *newArray_vectorlEvectorlEdoublegRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlEdoublegRsPgR(void *p);
   static void deleteArray_vectorlEvectorlEdoublegRsPgR(void *p);
   static void destruct_vectorlEvectorlEdoublegRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<double> >*)
   {
      vector<vector<double> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<double> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<double> >", -2, "vector", 386,
                  typeid(vector<vector<double> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEvectorlEdoublegRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<vector<double> >) );
      instance.SetNew(&new_vectorlEvectorlEdoublegRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlEdoublegRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlEdoublegRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlEdoublegRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlEdoublegRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<double> > >()));

      ::ROOT::AddClassAlternate("vector<vector<double> >","std::vector<std::vector<double, std::allocator<double> >, std::allocator<std::vector<double, std::allocator<double> > > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<vector<double> >*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvectorlEdoublegRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<vector<double> >*)0x0)->GetClass();
      vectorlEvectorlEdoublegRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvectorlEdoublegRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlEdoublegRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<double> > : new vector<vector<double> >;
   }
   static void *newArray_vectorlEvectorlEdoublegRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<double> >[nElements] : new vector<vector<double> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlEdoublegRsPgR(void *p) {
      delete ((vector<vector<double> >*)p);
   }
   static void deleteArray_vectorlEvectorlEdoublegRsPgR(void *p) {
      delete [] ((vector<vector<double> >*)p);
   }
   static void destruct_vectorlEvectorlEdoublegRsPgR(void *p) {
      typedef vector<vector<double> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<vector<double> >

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = 0);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 386,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));

      ::ROOT::AddClassAlternate("vector<int>","std::vector<int, std::allocator<int> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int>*)0x0)->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete ((vector<int>*)p);
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] ((vector<int>*)p);
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int>

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
   static TClass *vectorlEchargR_Dictionary();
   static void vectorlEchargR_TClassManip(TClass*);
   static void *new_vectorlEchargR(void *p = 0);
   static void *newArray_vectorlEchargR(Long_t size, void *p);
   static void delete_vectorlEchargR(void *p);
   static void deleteArray_vectorlEchargR(void *p);
   static void destruct_vectorlEchargR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<char>*)
   {
      vector<char> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<char>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<char>", -2, "vector", 386,
                  typeid(vector<char>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEchargR_Dictionary, isa_proxy, 0,
                  sizeof(vector<char>) );
      instance.SetNew(&new_vectorlEchargR);
      instance.SetNewArray(&newArray_vectorlEchargR);
      instance.SetDelete(&delete_vectorlEchargR);
      instance.SetDeleteArray(&deleteArray_vectorlEchargR);
      instance.SetDestructor(&destruct_vectorlEchargR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<char> >()));

      ::ROOT::AddClassAlternate("vector<char>","std::vector<char, std::allocator<char> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<char>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEchargR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<char>*)0x0)->GetClass();
      vectorlEchargR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEchargR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEchargR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<char> : new vector<char>;
   }
   static void *newArray_vectorlEchargR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<char>[nElements] : new vector<char>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEchargR(void *p) {
      delete ((vector<char>*)p);
   }
   static void deleteArray_vectorlEchargR(void *p) {
      delete [] ((vector<char>*)p);
   }
   static void destruct_vectorlEchargR(void *p) {
      typedef vector<char> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<char>

namespace {
  void TriggerDictionaryInitialization_S4RKFitterDict_Impl() {
    static const char* headers[] = {
"RKfitter.h",
"FieldMap.h",
"Histogram.h",
"TkrData.h",
"RungeKutta4.h",
0
    };
    static const char* includePaths[] = {
"../../include",
"/home/psmangeard/Programs/ROOT/root/include/",
"/media/psmangeard/DATA/Documents/UDEL/AESOPLITE2/AL2/Reconstruction/src/RKFitter/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "S4RKFitterDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TkrData.h")))  __attribute__((annotate("$clingAutoload$RKfitter.h")))  TkrData;
class __attribute__((annotate("$clingAutoload$FieldMap.h")))  __attribute__((annotate("$clingAutoload$RKfitter.h")))  FieldMap;
class __attribute__((annotate("$clingAutoload$RungeKutta4.h")))  __attribute__((annotate("$clingAutoload$RKfitter.h")))  RungeKutta4;
class __attribute__((annotate("$clingAutoload$RKfitter.h")))  RKfitter;
class __attribute__((annotate("$clingAutoload$Histogram.h")))  Histogram;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "S4RKFitterDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "RKfitter.h"
#include "FieldMap.h"
#include "Histogram.h"
#include "TkrData.h"
#include "RungeKutta4.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"FieldMap", payloadCode, "@",
"Histogram", payloadCode, "@",
"RKfitter", payloadCode, "@",
"RungeKutta4", payloadCode, "@",
"TkrData", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("S4RKFitterDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_S4RKFitterDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_S4RKFitterDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_S4RKFitterDict() {
  TriggerDictionaryInitialization_S4RKFitterDict_Impl();
}
