// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include <nholmann/json.hpp>
#include "GameDataManipulation.generated.h"

using json = nlohmann::json;

//USTRUCT(BlueprintType)
struct FCQ_Stats
{
	//GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Stats")
	float health;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Stats")
	float mana;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Stats")
	float attack;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Stats")
	float magic_attack;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Stats")
	float defense;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Stats")
	float magic_defense;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Stats")
	float armor;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Stats")
	float evasion;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Stats")
	float accuracy;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Stats")
	float agility;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Stats")
	float willpower;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Stats")
	float fire_res;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Stats")
	float water_res;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Stats")
	float earth_res;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Stats")
	float wind_res;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Stats")
	float ice_res;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Stats")
	float energy_res;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Stats")
	float nature_res;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Stats")
	float poison_res;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Stats")
	float metal_res;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Stats")
	float light_res;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Stats")
	float dark_res;

	FCQ_Stats() = default;
	FCQ_Stats(float in_health, float in_mana, float in_attack, float in_magic_attack, float in_defense,
		float in_magic_defense, float in_armor, float in_evasion, float in_accuracy, float in_agility, float in_willpower,
		float in_fire_res, float in_water_res, float in_earth_res, float in_wind_res, float in_ice_res, float in_energy_res,
		float in_nature_res, float in_poison_res, float in_metal_res, float in_light_res, float in_dark_res):
		health(in_health), mana(in_mana),attack(in_attack),magic_attack(in_magic_attack),defense(in_defense),
		magic_defense(in_magic_defense),armor(in_armor),evasion(in_evasion),accuracy(in_accuracy),agility(in_agility),
		willpower(in_willpower),fire_res(in_fire_res),water_res(in_water_res),earth_res(in_earth_res),wind_res(in_wind_res),
		ice_res(in_ice_res),energy_res(in_energy_res),nature_res(in_nature_res),metal_res(in_metal_res),light_res(in_light_res){}
};
//USTRUCT(BlueprintType)
struct FCQ_Item
{
	//GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Item")
	FString object_id;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Item")
	FString item_id;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Item")
	FString item_type;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Item")
	FString item_subtype;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Item")
	FString entity;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Item")
	FString name;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Item")
	int32 num;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Item")
	FString description;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Item")
	FCQ_Stats stats;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Item")
	float base_value;

	FCQ_Item() = default;
	FCQ_Item(const FString& in_item_id, const FString& in_item_type, const FString& in_item_subtype, /*... other parameters ...*/
		const FString& in_entity, const FString& in_name, int32 in_num, const FString& in_description, const FCQ_Stats& in_stats, float in_base_value) :
		item_id(in_item_id), item_type(in_item_type), item_subtype(in_item_subtype), /*... initialize other properties ...*/
		entity(in_entity), name(in_name), num(in_num),description(in_description), stats(in_stats), base_value(in_base_value) {}
};
//USTRUCT(BlueprintType)
struct FCQ_ItemRange
{
	//GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_ItemRange")
	TArray<FCQ_Item> collection;

	FCQ_ItemRange() = default;
	FCQ_ItemRange(const TArray<FCQ_Item>& in_collection) : collection(in_collection) {}
};
//USTRUCT(BlueprintType)
struct FCQ_Position {
	//GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Position")
	float pos_x;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Position")
	float pos_y;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Position")
	float pos_z;

	FCQ_Position() = default;
	FCQ_Position(const float& in_pos_x, const float& in_pos_y, const float& in_pos_z) :
		pos_x(in_pos_x), pos_y(in_pos_y), pos_z(in_pos_z) {}
};
//USTRUCT(BlueprintType)
struct FCQ_Purse
{
	//GENERATED_USTRUCT_BODY()

	//bits
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Purse")
	float Bits;

	FCQ_Purse() = default;
	FCQ_Purse(float in_bits) : Bits(in_bits) {}
};
//USTRUCT(BlueprintType)
struct FCQ_Inventory
{
	//GENERATED_USTRUCT_BODY()

	//purse,equipment,items
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Inventory")
	FString account_id;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Inventory")
	FCQ_Purse purse;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Inventory")
	FCQ_ItemRange items;

	FCQ_Inventory() = default;
	FCQ_Inventory(const FString& in_account_id, const FCQ_Purse& in_purse, const FCQ_ItemRange& in_items) :
		account_id(in_account_id), purse(in_purse), items(in_items) {}
};
//USTRUCT(BlueprintType)
struct FCQ_Loadout
{
	//GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Loadout")
	FCQ_Item head;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Loadout")
	FCQ_Item body;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Loadout")
	FCQ_Item feet;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Loadout")
	FCQ_Item weapon;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Loadout")
	FCQ_Item accessory_1;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Loadout")
	FCQ_Item accessory_2;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Loadout")
	FCQ_Item accessory_3;

	FCQ_Loadout() = default;
	FCQ_Loadout(const FCQ_Item& in_head, const FCQ_Item& in_body, const FCQ_Item& in_feet,
		const FCQ_Item& in_weapon, const FCQ_Item& in_accessory_1, const FCQ_Item& in_accessory_2, const FCQ_Item& in_accessory_3) :
		head(in_head), body(in_body), feet(in_feet), weapon(in_weapon), accessory_1(in_accessory_1), accessory_2(in_accessory_2),
		accessory_3(in_accessory_3) {}
};
//resident
//USTRUCT(BlueprintType)
struct FCQ_Resident 
{
	//GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CQ_Resident")
	FString objectID;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CQ_Resident")
	FString npc_id;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CQ_Resident")
	FString npc_name;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CQ_Resident")
	TArray<FString> dialogue;

	FCQ_Resident() = default;
	FCQ_Resident(const FString& in_objectID, const FString& in_npc_id,
		const FString& in_npc_name, const TArray<FString>& in_dialogue) :
		objectID(in_objectID), npc_id(in_npc_id), npc_name(in_npc_name), dialogue(in_dialogue) {}

};
//level
//USTRUCT(BlueprintType)
struct FCQ_Level 
{
	//GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CQ_Level")
	FString objectID;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Level")
	FString level_id;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Level")
	FString level_name;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Level")
	FString zip;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Level")
	TArray<FString> monsters;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Level")
	TArray<FString> residents;

	FCQ_Level() = default;
	FCQ_Level(const FString& in_objectID, const FString& in_level_id, const FString& in_level_name,
		const FString& in_zip, const TArray<FString>& in_monsters, const TArray<FString>& in_residents) :
		objectID(in_objectID), level_id(in_level_id), level_name(in_level_name), zip(in_zip),
		monsters(in_monsters), residents(in_residents) {}
};
//leveldata
//USTRUCT(BlueprintType)
struct FCQ_LevelData 
{
	//GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_LevelData")
	FCQ_Level level;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_LevelData")
	TArray<FCQ_Resident> residents;

	FCQ_LevelData() = default;
	FCQ_LevelData(const FCQ_Level& in_level, const TArray<FCQ_Resident>& in_residents) :
		level(in_level), residents(in_residents){}
};
//region
//USTRUCT(BlueprintType)
struct FCQ_Region 
{
	//GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Region")
	FString objectID;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Region")
	FString region_id;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Region")
	FString region_name;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Region")
	TArray<FString> levels;

	FCQ_Region() = default;
	FCQ_Region(const FString& in_objectID, const FString& in_region_id, const FString& in_region_name, const TArray<FString>& in_levels) :
		objectID(in_objectID), region_id(in_region_id), region_name(in_region_name),levels(in_levels) {}
};
//regiondata
//USTRUCT(BlueprintType)
struct FCQ_RegionData 
{
	//GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_RegionData")
	FCQ_Region region;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_RegionData")
	FCQ_LevelData level_data;

	FCQ_RegionData() = default;
	FCQ_RegionData(const FCQ_Region& in_region, const FCQ_LevelData& in_level_data) :
		region(in_region), level_data(in_level_data){}
};
//profile
//USTRUCT(BlueprintType)
struct FCQ_Profile 
{
	//GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CQ_Profile")
	FString objectID;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Profile")
	FString uuid;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Profile")
	FString name;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Profile")
	int32 level;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Profile")
	int32 age;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Profile")
	FString title;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Profile")
	float current_exp;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Profile")//
	float total_exp;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Profile")
	float max_exp;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Profile")
	FString race_id;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Profile")
	FString race_name;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Profile")
	FString class_id;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Profile")
	FString class_name;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Profile")
	FCQ_Position last_position;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Profile")
	FString last_region;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Profile")
	FString last_level;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Profile")
	FCQ_ItemRange items;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Profile")
	FCQ_Purse purse;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Profile")
	FCQ_Loadout loadout;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Profile")
	FCQ_Stats stats;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Profile")
	FCQ_Stats base_stats;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Profile")
	TArray<FString> spell_index;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_Profile")
	FString description;

	FCQ_Profile() = default;
	FCQ_Profile(const FString& in_objectID, const FString& in_uuid, const FString& in_name, const int32& in_level,
		const int32& in_age, const FString& in_title, const float& in_current_exp, const float& in_total_exp, const float& in_max_exp,
		const FString& in_race_id, const FString& in_race_name, const FString& in_class_id, const FString& in_class_name,
		const FCQ_Position& in_last_position, const FString& in_last_region, const FString& in_last_level, const FCQ_ItemRange& in_items,
		const FCQ_Purse& in_purse, const FCQ_Loadout& in_loadout, const FCQ_Stats& in_stats, const FCQ_Stats& in_base_stats,
		const TArray<FString>& in_spell_index, const FString& in_description) :
		objectID(in_objectID), uuid(in_uuid), name(in_name), level(in_level), age(in_age),title(in_title),current_exp(in_current_exp),
		total_exp(in_total_exp),max_exp(in_max_exp),race_id(in_race_id),race_name(in_race_name),class_id(in_class_id),class_name(in_class_name),
		last_position(in_last_position),last_region(in_last_region),last_level(in_last_level),items(in_items),purse(in_purse),loadout(in_loadout),
		stats(in_stats),base_stats(in_base_stats),spell_index(in_spell_index),description(in_description) {}
};
//user
//USTRUCT(BlueprintType)
struct FCQ_User
{
	//GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CQ_User")
	FString objectID;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_User")
	FString uuid;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_User")
	FString user_id;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_User")
	FString password;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_User")
	int32 active;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_User")
	int32 logins;
	
	FCQ_User() = default;
	FCQ_User(const FString& in_objectID, const FString& in_uuid, const FString& in_user_id, const FString& in_password, const int32& in_active, const int32& in_logins) :
		objectID(in_objectID), uuid(in_uuid), user_id(in_user_id), password(in_password), active(in_active), logins(in_logins) {}
};
//loginsecretpacket
//USTRUCT(BlueprintType)
struct FCQ_LSP 
{
	//GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_LSP")
	FCQ_User user_data;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_LSP")
	FCQ_Profile player_profile;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CQ_LSP")
	FCQ_RegionData region_data;

	FCQ_LSP() = default;
	FCQ_LSP(const FCQ_User& in_user_data, const FCQ_Profile& in_player_profile, const FCQ_RegionData& in_region_data) :
		user_data(in_user_data), player_profile(in_player_profile), region_data(in_region_data) {}
};
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameDataManipulation : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CQ2_API IGameDataManipulation
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	FCQ_Stats ToFCQ_Stats(std::string input);
	FCQ_Level ToFCQ_Level(std::string input);
	std::string& leftTrim(std::string& str, std::string& chars);
	std::string& rightTrim(std::string& str, std::string& chars);
	std::string& trimString(std::string& str, std::string& chars);
	std::vector<std::string> getContent(const std::string& input);
	std::vector<std::string> SplitString(const std::string& input, const std::string& separator);
};
