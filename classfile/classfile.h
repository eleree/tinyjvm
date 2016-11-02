#ifndef __TINY_JVM_CLASS_FILE_H__
#define __TINY_JVM_CLASS_FILE_H__

// Reference to https ://docs.oracle.com/javase/specs/jvms/se7/html/jvms-4.html

#include <stdint.h>
#include <stdio.h>

#pragma pack(1) 
typedef struct ClassFileHeader{
	uint32_t magicNumber;
	uint16_t minorVersion;
	uint16_t majorVersion;
	uint16_t constanPoolCount;
}ClassFileHeader;
#pragma pack()

typedef struct ConstantPoolItem
{
	struct ConstantPoolItem * next;
	void * itemInfo;
}ConstantPoolItem;

typedef struct ClassFile{
	uint8_t * data;
	ClassFileHeader header;	
	ConstantPoolItem * item;
}ClassFile;

enum ConstantType
{
	CONSTATNT_CLASS = 7,
	CONSTATNT_FIELDREF = 9,
	CONSTATNT_METHODREF = 10,
	CONSTATNT_INTERFACE_METHODREF = 11,
	CONSTATNT_STRING=8,
	CONSTATNT_INTEGER=3,
	CONSTATNT_FLOAT=4,
	CONSTATNT_LONG=5,
	CONSTATNT_DOUBLE=6,
	CONSTATNT_NAME_AND_TYPE=12,
	CONSTATNT_UTF8=1,
	CONSTATNT_METHOD_HANDLE=15,
	CONSTATNT_METHOD_TYPE=16,
	CONSTATNT_INVOKE_DYNAMIC=18,
};



// 4.4.The Constant Pool
// 4.4.1. The CONSTANT_Class_info Structure
typedef struct ConstantClassInfo{
	uint8_t tag;
	uint16_t nameIndex;
}ConstantClassInfo;

// 4.4.2. The CONSTANT_Fieldref_info, CONSTANT_Methodref_info, and CONSTANT_InterfaceMethodref_info Structures
typedef struct ConstantFieldrefInfo{
	uint8_t tag;
	uint16_t class_index;
	uint16_t name_and_type_index;
}ConstantFieldrefInfo;

typedef struct ConstantMethodrefInfo{
	uint8_t tag;
	uint16_t class_index;
	uint16_t name_and_type_index;
}ConstantMethodrefInfo;

typedef struct ConstantInterfaceMethodrefInfo{
	uint8_t tag;
	uint16_t class_index;
	uint16_t name_and_type_index;
}ConstantInterfaceMethodrefInfo;

// 4.4.3. The CONSTANT_String_info Structure
typedef struct ConstantStringInfo{
	uint8_t tag;
	uint16_t string_index;
}ConstantStringInfo;

// 4.4.4.The CONSTANT_Integer_info and CONSTANT_Float_info Structures
typedef struct ConstantIntegerInfo{
	uint8_t tag;
	uint32_t bytes;
}ConstantIntegerInfo;

typedef struct ConstantFloatInfo{
	uint8_t tag;
	uint32_t bytes;
}ConstantFloatInfo;

// 4.4.5.The CONSTANT_Long_info and CONSTANT_Double_info Structures
typedef struct ConstantLongInfo{
	uint8_t tag;
	uint32_t high_bytes;
	uint32_t low_bytes;
}ConstantLongInfo;

typedef struct ConstantDoubleInfo{
	uint8_t tag;
	uint32_t high_bytes;
	uint32_t low_bytes;
}ConstantDoubleInfo;

// 4.4.6.The CONSTANT_NameAndType_info Structure
typedef struct ConstantNameAndTypeInfo{
	uint8_t tag;
	uint16_t name_index;
	uint16_t descriptor_index;
}ConstantNameAndTypeInfo;

// 4.4.7.The CONSTANT_Utf8_info Structure
typedef struct ConstantUtf8Info{
	uint8_t tag;
	uint16_t length;
	uint8_t* bytes;
	//uint8_t bytes[length];
}ConstantUtf8Info;

// 4.4.8. The CONSTANT_MethodHandle_info Structure
typedef struct ConstantMethodHandleInfo{
	uint8_t tag;
	uint8_t reference_kind;
	uint16_t reference_index;
}ConstantMethodHandleInfo;

// 4.4.9.The CONSTANT_MethodType_info Structure
typedef struct ConstantMethodTypeInfo{
	uint8_t tag;
	uint16_t descriptor_index;
}ConstantMethodTypeInfo;


// 4.4.10.The CONSTANT_InvokeDynamic_info Structure
typedef struct ConstantInvokeDynamicInfo{
	uint8_t tag;
	uint16_t bootstrap_method_attr_index;
	uint16_t name_and_type_index;
}ConstantInvokeDynamicInfo;

// 4.7.Attributes
typedef struct AttributeInfo{
	uint16_t attributeNameIndex;
	uint32_t attributeLength;
	uint8_t * info;
	//uint8_t info[attribute_length];
}AttributeInfo;

// 4.7.2. The ConstantValue Attribute
typedef struct ConstantValueAttribute{
	uint16_t attribute_name_index;
	uint32_t attribute_length;
	uint16_t constantvalue_index;
}ConstantValueAttribute;

// 4.7.3.The Code Attribute
typedef struct CodeAttribute{
	uint16_t attribute_name_index;
	uint32_t attribute_length;
	uint16_t max_stack;
	uint16_t max_locals;
	uint32_t code_length;
	//uint8_t code[code_length];
	uint8_t *code;
	uint16_t exception_table_length;
	/*
	{   uint16_t start_pc;
	uint16_t end_pc;
	uint16_t handler_pc;
	uint16_t catch_type;
	} exception_table[exception_table_length];
	*/
	uint16_t attributes_count;
	//AttributeInfo attributes[attributes_count];
	AttributeInfo * attributes;
}CodeAttribute;

// 4.7.4. The StackMapTable Attribute
typedef struct StackMapTableAttribute{
	uint16_t              attribute_name_index;
	uint32_t              attribute_length;
	uint16_t              number_of_entries;
	//stack_map_frame entries[number_of_entries];
}StackMapTableAttribute;

// 4.7.5. The Exceptions Attribute
typedef struct ExceptionsAttribute{
	uint16_t attribute_name_index;
	uint32_t attribute_length;
	uint16_t number_of_exceptions;
	//uint16_t exception_index_table[number_of_exceptions];
	uint16_t * exception_index_table;
}ExceptionsAttribute;

// 4.7.6. The InnerClasses Attribute
typedef struct InnerClassesAttribute{
	uint16_t attribute_name_index;
	uint32_t attribute_length;
	uint16_t number_of_classes;
	/*
	{   uint16_t inner_class_info_index;
	uint16_t outer_class_info_index;
	uint16_t inner_name_index;
	uint16_t inner_class_access_flags;
	} classes[number_of_classes];
	*/
}InnerClassesAttribute;

// 4.7.7. The EnclosingMethod Attribute
typedef struct EnclosingMethodAttribute{
	uint16_t attribute_name_index;
	uint32_t attribute_length;
	uint16_t class_index;
	uint16_t method_index;
}EnclosingMethodAttribute;

// 4.7.8.The Synthetic Attribute
typedef struct SyntheticAttribute{
	uint16_t attribute_name_index;
	uint32_t attribute_length;
}SyntheticAttribute;

// 4.7.9.The Signature Attribute
typedef struct SignatureAttribute{
	uint16_t attribute_name_index;
	uint32_t attribute_length;
	uint16_t signature_index;
}SignatureAttribute;

// 4.7.10. The SourceFile Attribute
typedef struct SourceFileAttribute{
	uint16_t attribute_name_index;
	uint32_t attribute_length;
	uint16_t sourcefile_index;
}SourceFileAttribute;

// 4.7.11. The SourceDebugExtension Attribute
typedef struct SourceDebugExtensionAttribute{
	uint16_t attribute_name_index;
	uint32_t attribute_length;
	//uint8_t debug_extension[attribute_length];
	uint8_t * debug_extension;
}SourceDebugExtensionAttribute;

//4.7.12. The LineNumberTable Attribute
typedef struct LineNumberTableAttribute{
	uint16_t attribute_name_index;
	uint32_t attribute_length;
	uint16_t line_number_table_length;
	/*
	{   uint16_t start_pc;
	uint16_t line_number;
	} line_number_table[line_number_table_length];
	*/
}LineNumberTableAttribute;

// 4.7.13.The LocalVariableTable Attribute
typedef struct LocalVariableTableAttribute{
	uint16_t attribute_name_index;
	uint32_t attribute_length;
	uint16_t local_variable_table_length;
	/*
	{   uint16_t start_pc;
	uint16_t length;
	uint16_t name_index;
	uint16_t descriptor_index;
	uint16_t index;
	} local_variable_table[local_variable_table_length];
	*/
}LocalVariableTableAttribute;

// 4.7.14.The LocalVariableTypeTable Attribute
typedef struct LocalVariableTypeTableAttribute{
	uint16_t attribute_name_index;
	uint32_t attribute_length;
	uint16_t local_variable_type_table_length;
	/*
	{   uint16_t start_pc;
	uint16_t length;
	uint16_t name_index;
	uint16_t signature_index;
	uint16_t index;
	} local_variable_type_table[local_variable_type_table_length];
	*/
}LocalVariableTypeTableAttribute;

// 4.7.15. The Deprecated Attribute
typedef struct DeprecatedAttribute{
	uint16_t attribute_name_index;
	uint32_t attribute_length;
}DeprecatedAttribute;

//4.7.16.The RuntimeVisibleAnnotations attribute
typedef struct Annotation{
	int16_t type_index;
	int16_t num_element_value_pairs;
	/*
	{   int16_t            element_name_index;
	element_value value;
	} element_value_pairs[num_element_value_pairs];
	*/
}Annotation;

typedef struct RuntimeVisibleAnnotationsAttribute{
	uint16_t         attribute_name_index;
	uint32_t         attribute_length;
	uint16_t         num_annotations;
	//Annotation annotations[num_annotations];
	Annotation * annotations;
}RuntimeVisibleAnnotationsAttribute;

// 4.7.17. The RuntimeInvisibleAnnotations attribute
typedef struct RuntimeInvisibleAnnotationsAttribute{
	uint16_t         attribute_name_index;
	uint32_t         attribute_length;
	uint16_t         num_annotations;
	//Annotation annotations[num_annotations];
	Annotation * annotations;
}RuntimeInvisibleAnnotationsAttribute;

// 4.7.18.The RuntimeVisibleParameterAnnotations attribute
typedef struct RuntimeVisibleParameterAnnotationsAttribute{
	uint16_t attribute_name_index;
	uint32_t attribute_length;
	uint8_t num_parameters;
	//{   uint16_t         num_annotations;
	//Annotationannotations[num_annotations];
	//} parameter_annotations[num_parameters];
}RuntimeVisibleParameterAnnotationsAttribute;

// 4.7.19.The RuntimeInvisibleParameterAnnotations attribute
typedef struct RuntimeInvisibleParameterAnnotationsAttribute{
	uint16_t attribute_name_index;
	uint32_t attribute_length;
	uint8_t num_parameters;
	/*
	{   uint16_t         num_annotations;
	Annotationannotations[num_annotations];
	} parameter_annotations[num_parameters];
	*/
}RuntimeInvisibleParameterAnnotationsAttribute;

// 4.7.20.The AnnotationDefault attribute
typedef struct AnnotationDefaultAttribute{
	uint16_t            attribute_name_index;
	uint32_t            attribute_length;
	//element_value default_value;
}AnnotationDefaultAttribute;


// 4.7.21.The BootstrapMethods attribute
typedef struct BootstrapMethodsAttribute{
	uint16_t attribute_name_index;
	uint32_t attribute_length;
	uint16_t num_bootstrap_methods;
	//{   uint16_t bootstrap_method_ref;
	//uint16_t num_bootstrap_arguments;
	//uint16_t bootstrap_arguments[num_bootstrap_arguments];
	//} bootstrap_methods[num_bootstrap_methods];
}BootstrapMethodsAttribute;

// 4.5.Fields
typedef struct FieldInfo{
	uint16_t             access_flags;
	uint16_t             name_index;
	uint16_t             descriptor_index;
	uint16_t             attributes_count;
	//AttributeInfo attributes[attributes_count];
	AttributeInfo * attributes;
}FieldInfo;

// 4.6.Methods
typedef struct MethodInfo{
	uint16_t access_flags;
	uint16_t name_index;
	uint16_t descriptor_index;
	uint16_t attributes_count;
	//AttributeInfo attributes[attributes_count];
	AttributeInfo * attributes;
}MethodInfo;

ClassFile * parseClassData(uint8_t classData, uint64_t classSize);
void deleteClassFile(ClassFile * classFile);
int32_t printClassInfo(ClassFile * classFile);

#endif