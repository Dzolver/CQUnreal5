// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDataManipulation.h"
#include <vector>

using json = nlohmann::json;
// Add default functionality here for any IGameDataManipulation functions that are not pure virtual.

std::string& IGameDataManipulation::leftTrim(std::string& str, std::string& chars) {
	str.erase(0, str.find_first_not_of(chars));
	return str;
}

std::string& IGameDataManipulation::rightTrim(std::string& str, std::string& chars) {
	str.erase(str.find_last_not_of(chars) + 1);
	return str;
}

std::string& IGameDataManipulation::trimString(std::string& str, std::string& chars) {
	return leftTrim(rightTrim(str, chars), chars);
}

std::vector<std::string> IGameDataManipulation::SplitString(const std::string& input, const std::string& separator)
{
	std::vector<std::string> result;
	size_t pos = 0;
	size_t found;

	while ((found = input.find(separator, pos)) != std::string::npos) {
		result.push_back(input.substr(pos, found - pos));
		pos = found + separator.length();
	}

	result.push_back(input.substr(pos));
	return result;
}

std::vector<std::string> IGameDataManipulation::getContent(const std::string& input)
{
	//get content
	std::vector<std::string> partition1 = SplitString(input, "{");
	//get attribute
	std::string result1;
	if (partition1.size() > 2) {
		for (std::size_t i = 1; i < partition1.size(); ++i) {
			result1 += "{" + partition1[i];
		}
	}
	else {
		result1 = partition1[1];
	}
	std::vector<std::string> partition2 = SplitString(result1, ",");
	std::string root;
	std::vector<std::string> partition3;
	int i = 0;

	bool bracketOpened = false;
	bool bracketClosed = true;

	for (std::string& segment : partition2) {

		if (i == 0) {
			segment = segment.substr(1);
			root = segment;
		}
		//check if colon is found in segment
		bool colonFound = root.find(":") != std::string::npos;

		//check if left, right brackets are found to define composite conditions
		bool leftObject = root.find("{") != std::string::npos;
		bool rightObject = root.find("}") != std::string::npos;
		bool bothBracket = leftObject && rightObject;
		bool noBracket = !leftObject && !rightObject;

		//check if left, right array brackets are found to define composite conditions
		bool leftArray = root.find("[") != std::string::npos;
		bool rightArray = root.find("]") != std::string::npos;
		bool noArray = !leftArray && !rightArray;
		bool bothArray = leftArray && rightArray;

		//bracket toggling
		if (leftObject && !rightObject) {
			bracketOpened = true;
		}
		else if (rightObject && !leftObject) {
			bracketOpened = false;
			bracketClosed = true;
		}
		//if there are no colons with a (single right bracket and and a right array bracket), no colons with a (rightbracket and no array brackets at all)
		bool cond7 = !colonFound && ((rightObject && rightArray) || (rightObject && noArray));
		
		if (i > 0) {
			//partition3.push_back(segment)
			//check if segment has : symbol'
			//if root has a colon and closed brackets
			bool cond1 = colonFound && bracketClosed;
			//if root has a colon and no brackets at all and no arrays at all
			bool cond2 = colonFound && noBracket && noArray;
			//if root has a colon and closed brackets and closed arrays
			bool cond3 = colonFound && bracketClosed && bothArray;
			//if root has a colon and closed brackets and no arrays at all
			bool cond4 = colonFound && bracketClosed && noArray;
			//if root has a colon and no brackets at all and completed arrays
			bool cond5 = colonFound && noBracket && bothArray;
			//if root has a colon and completed brackets and completed arrays
			bool cond6 = colonFound && bothBracket && bothArray;

			if (cond1 || cond2 || cond3 || cond4 || cond5 || cond6) {
				// if so then ignore and replace stored segment with current segment
				//push stored string to partition3
				partition3.push_back(root);
				root = segment;
			}
			else if (cond7) {
				//  if not then attach to stored string
				root = root + "," + segment;
			}
			else {
				root = root + "," + segment;
			}
		}
		bracketClosed = false;
		i++;
	}
	//push the last stored string to partition3
	partition3.push_back(root);
	return partition3;
}

FCQ_Stats IGameDataManipulation::ToFCQ_Stats(std::string input)
{
	FCQ_Stats object;
	std::string chars_to_trim = "\"";
	std::map <std::string, float*> attributeMap = 
	{
		{"health",&object.health},
		{"mana",&object.mana},
		{"attack", &object.attack},
		{"magic_attack", &object.magic_attack},
		{"defense", &object.defense},
		{"magic_defense", &object.magic_defense},
		{"armor", &object.armor},
		{"evasion", &object.evasion},
		{"accuracy", &object.accuracy},
		{"agility", &object.agility},
		{"willpower", &object.willpower},
		{"fire_res", &object.fire_res},
		{"water_res", &object.water_res},
		{"earth_res", &object.earth_res},
		{"wind_res", &object.wind_res},
		{"ice_res", &object.ice_res},
		{"energy_res", &object.energy_res},
		{"nature_res", &object.nature_res},
		{"poison_res", &object.poison_res},
		{"metal_res", &object.metal_res},
		{"light_res", &object.light_res},
		{"dark_res", &object.dark_res}
	};
	//get content
	std::vector<std::string> partition1 = SplitString(input, "{");
	//get attribute
	std::vector<std::string> partition2 = SplitString(partition1[1], ",");
	for (const auto& attributeParts : partition2) {
		std::vector<std::string> attribute = SplitString(attributeParts, ":");
		std::string attributeName = trimString(attribute[0], chars_to_trim);
		float attributeValue = std::stof(attribute[1]);
		if (attributeMap.find(attributeName) != attributeMap.end()) {
			*(attributeMap[attributeName]) = attributeValue;
		}
	}
	//object.attack = input["attack"].get<float>();
	//object.magic_attack = input["magic_attack"].get<float>();
	//object.defense = input["defense"].get<float>();
	//object.magic_defense = input["magic_defense"].get<float>();
	//object.armor = input["armor"].get<float>();
	//object.evasion = input["evasion"].get<float>();
	//object.accuracy = input["accuracy"].get<float>();
	//object.agility = input["agility"].get<float>();
	//object.willpower = input["willpower"].get<float>();
	//object.fire_res = input["fire_res"].get<float>();
	//object.water_res = input["water_res"].get<float>();
	//object.earth_res = input["earth_res"].get<float>();
	//object.wind_res = input["wind_res"].get<float>();
	//object.ice_res = input["ice_res"].get<float>();
	//object.energy_res = input["energy_res"].get<float>();
	//object.nature_res = input["nature_res"].get<float>();
	//object.poison_res = input["poison_res"].get<float>();
	//object.metal_res = input["metal_res"].get<float>();
	//object.light_res = input["light_res"].get<float>();
	//object.dark_res = input["dark_res"].get<float>();
	return object;
}

FCQ_Level IGameDataManipulation::ToFCQ_Level(std::string input)
{
	FCQ_Level object;
	//std::map<std::string, std::string*> attributeMap =
	//{
	//	{"objectID",&object.objectID},
	//	{"level_id",&object.level_id},
	//	{"level_name",&object.level_name},
	//	{"zip",&object.zip},
	//	{"monsters",&object.monsters},
	//	{"residents",&object.residents}
	//};

	return FCQ_Level();
}
