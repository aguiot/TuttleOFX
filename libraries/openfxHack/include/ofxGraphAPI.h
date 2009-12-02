#ifndef _ofxGraphAPI_h_
#define _ofxGraphAPI_h_

// TUTTLE_TODO

#include "ofxCore.h"
#include "ofxAttribute.h"
#include "ofxParam.h"
#include "ofxClip.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief String used to label OFX Graph Plug-ins
 *
 * Set the pluginApi member of the OfxPluginHeader inside any OfxParamPluginStruct
 * to be this so that the host knows the plugin is an image effect.
 */
#define kOfxGraphPluginApi "OfxGraphPluginAPI"

/**
 * @brief The current version of the Param API
 */
#define kOfxGraphPluginApiVersion 1

/**
 * @defgroup ActionsParamAPI Actions Param API
 */
///@{

#define kOfxParamAPIGetTimeDomain "OfxParamAPIGetTimeDomain"
// GetTimeRangeNeeded is similar as the function GetFramesNeeded in ImageEffectAPI
#define kOfxParamAPIGetTimeRangeNeeded "OfxParamAPIGetTimeRangeNeeded"
#define kOfxParamAPIProcess "OfxParamAPIProcess"
#define kOfxParamAPIBeginSequenceProcess "OfxParamAPIBeginSequenceProcess"
#define kOfxParamAPIEndSequenceProcess "OfxParamAPIEndSequenceProcess"

///@}

/**
 * @defgroup PropertiesParamAPI Properties Param API
 */
///@{

#define kOfxPluginsNeeded "ofxPluginsNeeded"

///@}

typedef struct OfxGraphSuiteV1
{
	// plugins from core ( not the one instantiated in the Graph )

	OfxStatus ( *getNumberOfPlugins )( int* );
	OfxStatus ( *getPluginDescriptor )( int id, OfxPluginHandle* pluginDescriptor );
	OfxStatus ( *getPluginDescriptorFromName )( char* id, OfxPluginHandle* pluginDescriptor );

	OfxStatus ( *createNode )( OfxPluginHandle pluginDescriptor, OfxPluginHandle* node );

	OfxStatus ( *getPropertySet )( OfxGraphHandle graph, OfxPropertySetHandle* propHandle );

	// An attribute are input/ouput elements of the OfxPlugin ( can be clip, image clip, sound clip, params... )
	OfxStatus ( *getAttributeSet )( OfxGraphHandle graph, OfxAttributeSetHandle* attributeSet );
	OfxStatus ( *attributeGetHandle )( OfxAttributeSetHandle attributeSet, const char* name, OfxAttributeHandle* attribute, OfxPropertySetHandle* propertySet );
	OfxStatus ( *attributeGetPropertySet )( OfxAttributeHandle attribute, OfxPropertySetHandle* propHandle );

	OfxStatus ( *connectNodes )( OfxNodeHandle fromNode, OfxAttributeHandle fromAttribute, OfxNodeHandle toNode, OfxAttributeHandle toAttribute );
	OfxStatus ( *unconnectNodes )( OfxNodeHandle fromNode, OfxAttributeHandle fromAttribute, OfxNodeHandle toNode, OfxAttributeHandle toAttribute );
	// the exposed attribute is an output if the attribute from the inner node is itself an ouput, an input if the attribute from the inner node is itself an input
	OfxStatus ( *exposeAttribute )( OfxNodeHandle node, OfxAttributeHandle attribute, OfxPropertySetHandle propertySet );
	OfxStatus ( *unexposeAttribute )( OfxNodeHandle node, OfxAttributeHandle attribute, OfxPropertySetHandle propertySet );

} OfxGraphSuiteV1;

/*
 * --------------------------------------------------------------------------------
 *     ______________
 |             |
 |  Attribute  |
 |_____________|
 *      / \
 * ______/__     ___\___
 |         |   |       |
 |   Param |   |  Clip |
 |_________|   |_______|
 *
 * --------------------------------------------------------------------------------
 *       _______________________
 |                      |
 |         Node         | attributeList
 |______________________|
 *       /          | \
 * _______/___    ____|______    __\______________
 |           |  |           |  |                 |
 | ParamNode |  | GraphNode |  | ImageEffectNode | clipList
 |___________|  |___________|  |_________________| paramList
 *
 */

#ifdef __cplusplus
}
#endif

#endif

