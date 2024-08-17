#pragma once
#include "../pch.h"
#include "../vector/vector.h"
#include "../hacks/hacks.h"
#include "../hacks/hacks.h"

// Created with ReClass.NET 1.2 by KN4CK3R
class Entity
{
public:
	char pad_0000[48]; //0x0000
	Vector3 position; //0x0030
	float yaw; //0x003C
	float pitch; //0x0040
	char pad_0044[48]; //0x0044
	int8_t N000002D4; //0x0074
	int8_t N00000DFD; //0x0075
	int8_t N00000E01; //0x0076
	int8_t isAlive; //0x0077   // 1 is dead 0 is alive
	char pad_0078[252]; //0x0078
	int32_t marker; //0x0174
	int32_t displayHealth; //0x0178
	char pad_017C[16]; //0x017C
	int32_t currentWeapon; //0x018C
	int32_t isShooting; //0x0190
	int32_t random; //0x0194
	int32_t shotGun; //0x0198
	int32_t miniGun; //0x019C
	int32_t rocketLauncher; //0x01A0
	int32_t sniper; //0x01A4
	int32_t grenadeLauncher; //0x01A8
	int32_t pistol; //0x01AC
	char pad_01B0[192]; //0x01B0
	int32_t NN2893; //0x0270
	char name[7]; //0x0274
	char pad_027B[248]; //0x027B
	int32_t N000005E8; //0x0373
	int8_t N00000DF0; //0x0377
	char team[4]; //0x0378

	//IF I am out of a match or something this will not work because my health could be anything ect


	//Operator overloads(some use operator overloads from vector.h)
	bool operator==(const Entity& other) const {
		return this == &other;
	}
	explicit operator bool() const {
		return isAlive && displayHealth > 0 && displayHealth < 1000;
	}

	//copy constructor
	Entity(const Entity& other) {
		if (this != &other) {
			position = other.position;
			yaw = other.yaw;
			pitch = other.pitch;
			isAlive = other.isAlive;
			marker = other.marker;
			displayHealth = other.displayHealth;
			currentWeapon = other.currentWeapon;
			isShooting = other.isShooting;
			random = other.random;
			shotGun = other.shotGun;
			miniGun = other.miniGun;
			rocketLauncher = other.rocketLauncher;
			sniper = other.sniper;
			grenadeLauncher = other.grenadeLauncher;
			pistol = other.pistol;//*this = other
		}
	}
	//copy assignment
	Entity& operator=(const Entity& other) {
		if (this != &other) {  
			position = other.position;
			yaw = other.yaw;
			pitch = other.pitch;
			isAlive = other.isAlive;
			marker = other.marker;
			displayHealth = other.displayHealth;
			currentWeapon = other.currentWeapon;
			isShooting = other.isShooting;
			random = other.random;
			shotGun = other.shotGun;
			miniGun = other.miniGun;
			rocketLauncher = other.rocketLauncher;
			sniper = other.sniper;
			grenadeLauncher = other.grenadeLauncher;
			pistol = other.pistol;
		}
		return *this;
	}

	//move constructor
	Entity(Entity&& other) noexcept {
		position = other.position;
		yaw = other.yaw;
		pitch = other.pitch;
		isAlive = other.isAlive;
		marker = other.marker;
		displayHealth = other.displayHealth;
		currentWeapon = other.currentWeapon;
		isShooting = other.isShooting;
		random = other.random;
		shotGun = other.shotGun;
		miniGun = other.miniGun;
		rocketLauncher = other.rocketLauncher;
		sniper = other.sniper;
		grenadeLauncher = other.grenadeLauncher;
		pistol = other.pistol;

		memset(&other, 0, sizeof(Entity));
	}
	//move assingment
	Entity& operator=(Entity&& other) noexcept {
		if (this != &other) {
			position = other.position;
			yaw = other.yaw;
			pitch = other.pitch;
			isAlive = other.isAlive;
			marker = other.marker;
			displayHealth = other.displayHealth;
			currentWeapon = other.currentWeapon;
			isShooting = other.isShooting;
			random = other.random;
			shotGun = other.shotGun;
			miniGun = other.miniGun;
			rocketLauncher = other.rocketLauncher;
			sniper = other.sniper;
			grenadeLauncher = other.grenadeLauncher;
			pistol = other.pistol;

			std::memset(&other, 0, sizeof(Entity));
		}
		return *this;
	}
	Vector3 getDelta(const Entity& entity) const;

}; //Size: 0x1604
//static_assert(sizeof(Entity) == 0x1604);
