#include"GameManager.h"
#include "BoxCollider.h"


namespace SDLFramework {

	GameManager* GameManager::sInstance = nullptr;

	GameManager* GameManager::Instance() {
		if (sInstance == nullptr) {
			sInstance = new GameManager();
		}
		return sInstance;
	}

	void GameManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}

	void GameManager::Run() {
		//main game 
		while (!mQuit) {
			mTimer->Update();
			//event polling loop
			while (SDL_PollEvent(&mEvents))
			{
				switch (mEvents.type) {
				case SDL_QUIT:
					mQuit = true;
					break;
				}
			}

			if (mTimer->DeltaTime() >= 1.0f / Frame_Rate) {
				mTimer->Reset();
				update();
				lateUpdate();
				Render();
			}

		}

	}

	void GameManager::update() {
		mInputManager->Update();

		if (mInputManager->KeyDown(SDL_SCANCODE_W)) {
			mPhysOne->Translate(vector2(0, -40.0f) * mTimer->DeltaTime(), GameEntity::World);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_S)) {
			mPhysOne->Translate(vector2(0, 40.0f) * mTimer->DeltaTime(), GameEntity::World);
		}
		if (mInputManager->KeyDown(SDL_SCANCODE_A)) {
			mPhysOne->Translate(vector2(-40.f, 0) * mTimer->DeltaTime(), GameEntity::World);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_D)) {
			mPhysOne->Translate(vector2(40.0f, 0) * mTimer->DeltaTime(), GameEntity::World);
		}
		
		
	

	}
	void GameManager::lateUpdate() {
		mPhysicsManager->Update();
		mInputManager->UpdatePrevInput();

	}

	void GameManager::Render() {
		mGraphics->ClearBackBuffer();

		

		mPhysOne->Render();
		mPhysTwo->Render();
		mPhysThree->Render();
		mPhysFour->Render();

		

		mGraphics->Render();
	}

	GameManager::GameManager() : mQuit(false){
		mGraphics = Graphics::Instance();

		if (!Graphics::Initialized()) {
			mQuit = true;
		}

		//Init all modules here
		mTimer = Timer::Instance();

		mAssetManager = AssetManager::Instance();
		mInputManager = InputManager::Instance();
		mAudioManager = AudioManager::Instance();
		mPhysicsManager = PhysicsManager::Instance();

		


	}

	GameManager::~GameManager() {

		

		Graphics::Release();
		mGraphics = nullptr;

		Timer::Release();
		mTimer = nullptr;

		AssetManager::Release();
		mAssetManager = nullptr;

		InputManager::Release();
		mInputManager = nullptr;

		AudioManager::Release();
		mAudioManager = nullptr;

		PhysicsManager::Release();
		mPhysicsManager = nullptr;

		SDL_Quit();
	}

//namespace 
}