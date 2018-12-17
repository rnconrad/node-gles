/**
 * @license
 * Copyright 2018 Google Inc. All Rights Reserved.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * =============================================================================
 */

#include "webgl_extensions.h"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "utils.h"

namespace nodejsgl {

//==============================================================================
// WebGL_LoseContextExtension

napi_ref WebGL_LoseContextExtension::constructor_ref_;

WebGL_LoseContextExtension::WebGL_LoseContextExtension(napi_env env)
    : env_(env), ref_(nullptr) {}

WebGL_LoseContextExtension::~WebGL_LoseContextExtension() {
  // TODO(kreeger): Auto-clean this up with inheritance?
  napi_delete_reference(env_, ref_);
}

/* static */
napi_status WebGL_LoseContextExtension::Register(napi_env env,
                                                 napi_value exports) {
  napi_status nstatus;

  napi_property_descriptor properties[] = {
      NAPI_DEFINE_METHOD("loseContext", LoseContext),
      NAPI_DEFINE_METHOD("restoreContext", RestoreContext),
  };

  napi_value ctor_value;
  nstatus = napi_define_class(env, "WEBGL_lose_context", NAPI_AUTO_LENGTH,
                              WebGL_LoseContextExtension::InitInternal, nullptr,
                              ARRAY_SIZE(properties), properties, &ctor_value);

  nstatus = napi_create_reference(env, ctor_value, 1, &constructor_ref_);
  ENSURE_NAPI_OK_RETVAL(env, nstatus, nstatus);

  return napi_ok;
}

/* static  */
napi_status WebGL_LoseContextExtension::NewInstance(napi_env env,
                                                    napi_value* instance) {
  napi_status nstatus;

  napi_value ctor_value;
  nstatus = napi_get_reference_value(env, constructor_ref_, &ctor_value);
  ENSURE_NAPI_OK_RETVAL(env, nstatus, nstatus);

  nstatus = napi_new_instance(env, ctor_value, 0, nullptr, instance);
  ENSURE_NAPI_OK_RETVAL(env, nstatus, nstatus);

  return napi_ok;
}

/* static */
napi_value WebGL_LoseContextExtension::InitInternal(napi_env env,
                                                    napi_callback_info info) {
  napi_status nstatus;

  ENSURE_CONSTRUCTOR_CALL_RETVAL(env, info, nullptr);

  napi_value js_this;
  nstatus = napi_get_cb_info(env, info, 0, nullptr, &js_this, nullptr);
  ENSURE_NAPI_OK_RETVAL(env, nstatus, nullptr);

  // TODO(kreeger): If this is a stub class - can probably just define a JS
  // object with no-op methods.
  WebGL_LoseContextExtension* context = new WebGL_LoseContextExtension(env);
  ENSURE_VALUE_IS_NOT_NULL_RETVAL(env, context, nullptr);

  nstatus = napi_wrap(env, js_this, context, Cleanup, nullptr, &context->ref_);
  ENSURE_NAPI_OK_RETVAL(env, nstatus, nullptr);

  return js_this;
}

/* static */
void WebGL_LoseContextExtension::Cleanup(napi_env env, void* native,
                                         void* hint) {
  WebGL_LoseContextExtension* extension =
      static_cast<WebGL_LoseContextExtension*>(native);
  delete extension;
}

/* static */
napi_value WebGL_LoseContextExtension::LoseContext(napi_env env,
                                                   napi_callback_info info) {
  // TODO(kreeger): No-op OK?
  return nullptr;
}

/* static */
napi_value WebGL_LoseContextExtension::RestoreContext(napi_env env,
                                                      napi_callback_info info) {
  // TODO(kreeger): No-op OK?
  return nullptr;
}

//==============================================================================
// WebGL_OESTextureHalfFloatExtension

napi_ref WebGL_OESTextureHalfFloatExtension::constructor_ref_;

WebGL_OESTextureHalfFloatExtension::WebGL_OESTextureHalfFloatExtension(
    napi_env env)
    : env_(env), ref_(nullptr) {}

WebGL_OESTextureHalfFloatExtension::~WebGL_OESTextureHalfFloatExtension() {
  // TODO(kreeger): Auto-clean this up with inheritance?
  napi_delete_reference(env_, ref_);
}

/* static */
napi_status WebGL_OESTextureHalfFloatExtension::Register(napi_env env,
                                                         napi_value exports) {
  napi_status nstatus;

  napi_property_descriptor properties[] = {NapiDefineIntProperty(
      env, GL_HALF_FLOAT_OES, "HALF_FLOAT_OES")};  // TODO find def

  napi_value ctor_value;
  nstatus = napi_define_class(env, "OES_texture_half_float", NAPI_AUTO_LENGTH,
                              WebGL_OESTextureHalfFloatExtension::InitInternal,
                              nullptr, ARRAY_SIZE(properties), properties,
                              &ctor_value);
  ENSURE_NAPI_OK_RETVAL(env, nstatus, nstatus);

  nstatus = napi_create_reference(env, ctor_value, 1, &constructor_ref_);
  ENSURE_NAPI_OK_RETVAL(env, nstatus, nstatus);

  return napi_ok;
}

/* static */
napi_status WebGL_OESTextureHalfFloatExtension::NewInstance(
    napi_env env, napi_value* instance) {
  // TODO - write me.

  return napi_ok;
}

/* static */
napi_value WebGL_OESTextureHalfFloatExtension::InitInternal(
    napi_env env, napi_callback_info info) {
  // TODO - write me.
  return nullptr;
}

/* static */
void WebGL_OESTextureHalfFloatExtension::Cleanup(napi_env env, void* native,
                                                 void* hint) {
  WebGL_OESTextureHalfFloatExtension* extension =
      static_cast<WebGL_OESTextureHalfFloatExtension*>(native);
  delete extension;
}

}  // namespace nodejsgl
