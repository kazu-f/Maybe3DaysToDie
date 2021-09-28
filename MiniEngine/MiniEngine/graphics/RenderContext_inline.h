#include "RenderContext.h"
#pragma once

namespace Engine {
	inline void RenderContext::SetDescriptorHeap(DescriptorHeap& descHeap)
	{
		m_descriptorHeaps[0] = descHeap.Get();
		m_commandList->SetDescriptorHeaps(1, m_descriptorHeaps);

		//�f�B�X�N���v�^�e�[�u���ɓo�^����B
		if (descHeap.IsRegistConstantBuffer()) {
			SetGraphicsRootDescriptorTable(0, descHeap.GetConstantBufferGpuDescritorStartHandle());
		}
		if (descHeap.IsRegistShaderResource()) {
			SetGraphicsRootDescriptorTable(1, descHeap.GetShaderResourceGpuDescritorStartHandle());
		}
		if (descHeap.IsRegistUavResource()) {
			SetGraphicsRootDescriptorTable(2, descHeap.GetUavResourceGpuDescritorStartHandle());
		}
	}
	inline void RenderContext::SetComputeDescriptorHeap(DescriptorHeap& descHeap)
	{
		m_descriptorHeaps[0] = descHeap.Get();
		m_commandList->SetDescriptorHeaps(1, m_descriptorHeaps);

		//�f�B�X�N���v�^�e�[�u���ɓo�^����B
		if (descHeap.IsRegistConstantBuffer()) {
			SetComputeRootDescriptorTable(0, descHeap.GetConstantBufferGpuDescritorStartHandle());
		}
		if (descHeap.IsRegistShaderResource()) {
			SetComputeRootDescriptorTable(1, descHeap.GetShaderResourceGpuDescritorStartHandle());
		}
		if (descHeap.IsRegistUavResource()) {
			SetComputeRootDescriptorTable(2, descHeap.GetUavResourceGpuDescritorStartHandle());
		}
	}
	inline void RenderContext::WaitUntilFinishDrawingToRenderTarget(RenderTarget& renderTarget)
	{
		WaitUntilFinishDrawingToRenderTarget(renderTarget.GetRenderTargetTexture().Get());
	}
	inline void RenderContext::WaitUntilToPossibleSetRenderTarget(RenderTarget& renderTarget)
	{
		WaitUntilToPossibleSetRenderTarget(renderTarget.GetRenderTargetTexture().Get());
	}
	inline void RenderContext::WaitUntilToPossibleSetRenderTargets(int numRt, RenderTarget* renderTargets[])
	{
		for (int i = 0; i < numRt; i++) {
			WaitUntilToPossibleSetRenderTarget(*renderTargets[i]);
		}
	}
	inline void RenderContext::WaitUntilFinishDrawingToRenderTargets(int numRt, RenderTarget* renderTargets[])
	{
		for (int i = 0; i < numRt; i++) {
			WaitUntilFinishDrawingToRenderTarget(*renderTargets[i]);
		}
	}
	inline void RenderContext::SetRenderTargetAndViewport(RenderTarget* renderTarget)
	{
		D3D12_VIEWPORT viewport;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = static_cast<float>(renderTarget->GetWidth());
		viewport.Height = static_cast<float>(renderTarget->GetHeight());
		viewport.MinDepth = D3D12_MIN_DEPTH;
		viewport.MaxDepth = D3D12_MAX_DEPTH;
		SetViewport(viewport);
		SetRenderTarget(renderTarget);
	}
	inline void RenderContext::SetRenderTarget(RenderTarget* renderTarget)
	{
		auto rtvHandle = renderTarget->GetRTVCpuDescriptorHandle();
		if (renderTarget->IsExsitDepthStencilBuffer())
		{
			auto dsvHandle = renderTarget->GetDSVCpuDescriptorHandle();
			m_commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);
		}
		else {
			//�f�v�X�X�e���V���o�b�t�@�͂Ȃ��B
			m_commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);
		}
	}
	inline void RenderContext::SetRenderTargets(UINT numRT, RenderTarget* renderTargets[])
	{
		//d
		D3D12_CPU_DESCRIPTOR_HANDLE rtDSHandleTbl[32];
		int rtNo = 0;
		for (int rtNo = 0; rtNo < static_cast<int>(numRT); rtNo++) {
			rtDSHandleTbl[rtNo] = renderTargets[rtNo]->GetRTVCpuDescriptorHandle();
		}
		D3D12_CPU_DESCRIPTOR_HANDLE dsDS = renderTargets[0]->GetDSVCpuDescriptorHandle();
		m_commandList->OMSetRenderTargets(numRT, rtDSHandleTbl, FALSE, &dsDS);

	}
	inline void RenderContext::ClearRenderTargetViews(int numRt, RenderTarget* renderTargets[])
	{
		ClearDepthStencilView(renderTargets[0]->GetDSVCpuDescriptorHandle(), renderTargets[0]->GetDSVClearValue());
		for (int i = 0; i < numRt; i++) {
			ClearRenderTargetView(renderTargets[i]->GetRTVCpuDescriptorHandle(), renderTargets[i]->GetRTVClearColor());
		}
	}
}