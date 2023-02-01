/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Tencent is pleased to support the open source community by making libpag available.
//
//  Copyright (C) 2021 THL A29 Limited, a Tencent company. All rights reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file
//  except in compliance with the License. You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  unless required by applicable law or agreed to in writing, software distributed under the
//  license is distributed on an "as is" basis, without warranties or conditions of any kind,
//  either express or implied. see the license for the specific language governing permissions
//  and limitations under the license.
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "TextureSource.h"
#include "core/utils/Log.h"

namespace tgfx {
TextureSource::TextureSource(std::shared_ptr<Texture> texture)
    : proxy(TextureProxy::Wrap(std::move(texture))) {
}

bool TextureSource::isAlphaOnly() const {
  auto texture = proxy->getTexture();
  DEBUG_ASSERT(texture != nullptr);
  return texture->getSampler()->format == PixelFormat::ALPHA_8;
}

std::shared_ptr<TextureProxy> TextureSource::lockTextureProxy(Context* context) const {
  auto texture = proxy->getTexture();
  DEBUG_ASSERT(texture != nullptr);
  if (texture->getContext() != context) {
    return nullptr;
  }
  return proxy;
}

std::shared_ptr<TextureProxy> TextureSource::onMakeTextureProxy(Context*) const {
  return nullptr;
}
}  // namespace tgfx