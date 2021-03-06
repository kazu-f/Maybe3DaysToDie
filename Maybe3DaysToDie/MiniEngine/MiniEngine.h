#pragma once

#pragma comment( lib, "xinput.lib")

#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <math.h>
#include <vector>
#include <list>
#include <D3Dcompiler.h>
#include <Windows.h>
#include <wincodec.h>
#include <wincodecsdk.h>
#include <d3d12.h>
#include <map>
#include <functional>
#include <algorithm>
#include <DirectXMath.h>
#include <Xinput.h>
#include <xaudio2.h>
#include <x3daudio.h>
#include <xaudio2fx.h>
#include <array>
#include <queue>
#include <fstream>
#include <mbstring.h>
#include <mmsystem.h>

#include "dxgi.h"
#include "d3dx12.h"

//SpriteBatch.
#include "DirectXTK/Inc/SpriteFont.h"

//Effekseerのヘッダーファイルをインクルード。
#include "Effekseer.h"
#include "EffekseerRendererDX12.h"

#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"

#include "policy/Noncopyable.h"
#include "system/debugLog.h"
#include "math/Math.h"
#include "math/Vector.h"
#include "math/Matrix.h"

const int MAX_RENDERING_TARGET = D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT;	//レンダリングターゲットの最大数。

#include "graphics/GPUBuffer/VertexBuffer.h"
#include "graphics/GPUBuffer/IndexBuffer.h"
#include "graphics/IShaderResource.h"
#include "graphics/IUnorderAccessResource.h"
#include "graphics/Texture.h"
#include "graphics/GPUBuffer/RWStructuredBuffer.h"
#include "graphics/Shader.h"
#include "graphics/PipelineState.h"
#include "graphics/GPUBuffer/ConstantBuffer.h"
#include "graphics/RootSignature.h"
#include "graphics/GraphicsEngine.h"
#include "graphics/DescriptorHeap.h"
#include "graphics/RenderTarget.h"

#include "gameObject/GameObjectManager.h"


#include "graphics/IRenderer.h"
#include "graphics/2D/Sprite.h"
#include "graphics/Font/FontRender.h"

#include "HID/GamePad.h"
#include "util/NameKey.h"
#include "util/CGameTime.h"
#include "util/TResourceBank.h"
#include "util/Noise.h"
#include "tkFile/TkmFile.h"
#include "tkFile/TksFile.h"

#include "ResourceEngine.h"
#include "physics/PhysicsWorld.h"
#include "Sound/SoundEngine.h"
#include "tkEngine.h"
#include "physics/PhysicsStaticObject.h"
#include "physics/PhysicsGhostobject.h"
#include "characterController/CharacterController.h"
#include "physics/CollisionAttr.h"

#include "graphics/RenderContext_inline.h"
#include "graphics/DescriptorHeap_inline.h"
#include "graphics/Skeleton.h"
#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"
#include "graphics/animation/AnimationPlayController.h"
#include "prefab/ModelRender.h"
#include "prefab/SpriteRender.h"
#include "prefab/light/DirectionLight.h"
#include "graphics/light/LightManager.h"
#include "level/Level.h"
#include "Sound/SoundSource.h"
#include "prefab/nature/Sky.h"

#include "graphics/RendererManager.h"
#include "graphics/PreRender/ShadowMap.h"
#include "graphics/PreRender/GBufferRender.h"
#include "graphics/defferd/DefferdShading.h"
#include "graphics/PostEffect/PostEffect.h"
#include "graphics/Fade.h"

#include "graphics/PipelineStatesDefault.h"

#include "system/system.h"

const UINT FRAME_BUFFER_W = 1280;				//フレームバッファの幅。
const UINT FRAME_BUFFER_H = 720;				//フレームバッファの高さ。

static const int MAX_BONE = 512;				//ボーンの最大数。

using namespace Engine;

#include "Mause/MauseInfo.h"
