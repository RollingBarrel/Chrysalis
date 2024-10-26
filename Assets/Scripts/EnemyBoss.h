#pragma once
#include "Enemy.h"
#include "float2.h"
#include <vector>
#include <map>

struct CollisionData;
class BoxColliderComponent;
class ImageComponent;

enum BulletPattern
{
	CIRCLES,
	ARROW,
	WAVE,
	TARGETED_CIRCLES,
	NONE
};
GENERATE_BODY(EnemyBoss);
class EnemyBoss : public Enemy
{
	FRIEND(EnemyBoss)

public:
	EnemyBoss(GameObject* owner);
	~EnemyBoss() {}
	void Update() override;
	void Start() override;
	void TakeDamage(float damage) override;
	float GetBombsDelay() const { return mBombsDelay; }
	inline void LookAt(float3 direction, float time);
	void LookAtS(float3 direction, float speed) { LookAt(direction.xz(), speed); }
	void LookAt(float2 direction, float speed);
	void WakeUp() { mWakeUp = true; }

private:
	void UpdatePhase1();
	void UpdatePhase2();
	void UpdatePhase3();
	void StartBulletAttack(BulletPattern pattern);
	void BulletHellPattern1();
	void BulletHellPattern2();
	void BulletHellPattern3();
	void BulletHellPattern4();
	void BulletHellPattern5();
	void BulletHellPattern6();
	void LaserAttack();
	void BombAttack(const char* pattern);
	void SetupBomb(GameObject* bombGO, const math::float3& position);
	void Rotate();
	void InterruptAttacks();
	void SwitchMaterial(int uuid);

	void CheckHitEffect() override;
	void  Death() override;

	int mLastAttack = -1;
	float3 mFront = float3::unitX;
	float mTargetRotation = 0.0f;
	unsigned int mStage = 0;
	float mPhase1Hp = 0.6f;
	float mPhase2Hp = 0.3f;
	bool mWakeUp = false;
	bool mInvulnerable = true;
	float mSpawnOffsetY = 0.0f;
	float3 mOgPosition = float3::zero;

	GameObject* mShieldGO = nullptr;
	ImageComponent* mSpritesheet = nullptr;

	//Collider
	BoxColliderComponent* mCollider = nullptr;

	TimerScript mPhaseShiftTimer;
	float mPhaseShiftTime = 5.0f;
	TimerScript mBulletHellTimer;
	TimerScript mShieldTimer;
	float mShieldDelay = 200.0f;

	float mAttackSequenceCooldown = 4.0f;

	// Bullet Hell
	float mBulletHellDuration = 5.0f;
	float mBulletSpeed = 15.0f;
	float mBulletsDamage = 2.0f;
	float mBulletRange = 50.0f;
	unsigned int mBulletsWave = 0;
	BulletPattern mBulletHell = BulletPattern::NONE;

	//Laser
	float mLaserDuration = 6.0f;
	float mLaserDamage = 3.0f;
	float mLaserSpeed = 2.0f;
	float mLaserDistance = 15.0f;
	
	//Bombs
	float mBombDamage = 5.0f;
	float mBombsDelay = 1.f;
	float mBombsDuration = 2.0f;

	GameObject* mAreas[3] = { nullptr, nullptr, nullptr};
	std::vector<float3> mAreaPositions;
	std::map<float, int> mPlayerAreaDistances;
	const char* mTemplateNames[4] = { "BombingTemplate1.prfb", "BombingTemplate2.prfb", "BombingTemplate3.prfb", "BombingTemplateSingle.prfb"};
	std::vector<GameObject*> mTemplates;
	GameObject* mLaserGO = nullptr;
	GameObject* mDeathParticlesHead = nullptr;
	GameObject* mDeathParticlesBody = nullptr;
	GameObject* mDeathParticlesLegs = nullptr;
	const int mPhase2MatId = 1639454952;
	const int mPhase3MatId = 577614609;
};

