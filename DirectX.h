/*=============================================================================

		DirectX�ݒ�[ DirectX.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/24
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/24
=============================================================================*/

#ifndef _DIRECTX_H_
#define _DIRECTX_H_

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include <d3dx9.h>
#include <crtdbg.h>
#include <Xinput.h>

/*-----------------------------------------------------------------------------
	�}�N����`
-----------------------------------------------------------------------------*/
#define SCREEN_WIDTH   ( 800 )	//	�E�C���h�E�̕�
#define SCREEN_HEIGHT  ( 600 )	//	�E�C���h�E�̍���

//	���_�t�H�[�}�b�g
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//	2D
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL)	//	3D

#define NUM_VERTEX ( 4 )	//	���_��
#define NUM_POLYGON ( 2 )	//	�|���S����

#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)	//	���������[�N���o(�o�̓f�o�b�O�ɕ\�������)

/*-----------------------------------------------------------------------------
	 ���C�u�����t�@�C��
	 [�\���v���p�e�B]->[�����J�[]->[����]->[�ǉ��̈ˑ��t�@�C��]�ɋL�q���Ă��\
-----------------------------------------------------------------------------*/
#pragma comment(lib , "d3d9.lib")
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <XAudio2.h>

#pragma comment(lib, "xinput.lib")	//	XInput
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")	//	�V�X�e�������擾�ɕK�v
#pragma comment(lib, "dinput8.lib")

/*-----------------------------------------------------------------------------
	�\����
-----------------------------------------------------------------------------*/
struct VERTEX_2D
{
	D3DXVECTOR3 Pos;	//	���_���W
	float Rhw;			//	���W�ϊ��ςݒ��_�t���O�iDirectX�ɂ����Ȃ��d�l�j�K��1.0f������
	D3DCOLOR Color;		//	���_�J���[
	D3DXVECTOR2 Tex;	//	�e�N�X�`�����W
};

struct VERTEX_3D
{
	D3DXVECTOR3 Pos;	//	���_���W
	D3DXVECTOR3 Nor;	//	�@��
	D3DCOLOR Color;		//	���_�J���[
	D3DXVECTOR2 Tex;	//	�e�N�X�`�����W
};

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CDirectX
{
public:
	static HRESULT Init(HWND Wnd, bool Window);	//	������
	static void Uninit(void);					//	�I��

	static void DrawBegin(void);	//	�`��̊J�n
	static void DrawEnd(void);		//	�`��̏I��

	//	Getter
	static LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	//	�f�o�C�X

private:
	//	�f�o�C�X�̏�����
	static void SetUpDevice(D3DPRESENT_PARAMETERS d3dpp, D3DDISPLAYMODE d3ddm, HWND Wnd, bool Window);
	static void SetRenderState(void);			//	�����_�[�X�e�[�g�̐ݒ�
	static void SetSamplerState(void);			//	�T���v���[�X�e�[�g�̐ݒ�
	static void SetTextureStageState(void);		//	�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�

#ifdef _DEBUG
	static void DrawFPS(void);	//	FPS�\��
#endif

private:
	static D3DXCOLOR m_BackBufferColor;				//	�o�b�N�o�b�t�@�F

	static LPDIRECT3D9				m_pD3D;			// Direct3D�I�u�W�F�N�g
	static LPDIRECT3DDEVICE9		m_pD3DDevice;	// Device�I�u�W�F�N�g(�`��ɕK�v)

#ifdef _DEBUG
	static LPD3DXFONT m_Font;	// �t�H���g�ւ̃|�C���^
#endif
};
#endif
