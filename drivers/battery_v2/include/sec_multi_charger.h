/*
 * sec_multi_charger.h
 * Samsung Mobile Charger Header
 *
 * Copyright (C) 2015 Samsung Electronics, Inc.
 *
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#ifndef __SEC_MULTI_CHARGER_H
#define __SEC_MULTI_CHARGER_H __FILE__

#include <linux/of_gpio.h>
#include "sec_charging_common.h"

#define SEC_SUB_CHARGER_CONDITION_NONE			0x00
#define SEC_SUB_CHARGER_CONDITION_ONLINE		0x01
#define SEC_SUB_CHARGER_CONDITION_CV			0x02
#define SEC_SUB_CHARGER_CONDITION_CHARGE_DONE	0x04
#define SEC_SUB_CHARGER_CONDITION_CURRENT_MAX	0x10
#define SEC_SUB_CHARGER_CONDITION_CURRENT_NOW	0x20
#define SEC_SUB_CHARGER_CONDITION_FAST_CURRENT	0x40
#define SEC_SUB_CHARGER_CONDITION_CHARGE_POWER	0x80

#define SEC_SUB_CHARGER_CURRENT_MARGIN			100

#define SEC_MULTI_CHARGER_TEST_MASTER_MODE_CURRENT	1450
#define SEC_MULTI_CHARGER_TEST_SLAVE_MODE_CURRENT	700

enum sec_multi_charger_mode {
	SEC_MULTI_CHARGER_NORMAL = 0, /* Main Charger Default ON;  Sub charger: depend on sub_charger_condition */
	SEC_MULTI_CHARGER_MAIN_ONLY,
	SEC_MULTI_CHARGER_SUB_ONLY,
	SEC_MULTI_CHARGER_ALL_ENABLE,
	SEC_MULTI_CHARGER_LOAD_SWITCH_CHARGING_OFF,
	SEC_MULTI_CHARGER_LOAD_SWITCH_CHARGING_ON,
};

struct sec_multi_charger_platform_data {
	char *battery_name;
	char *main_charger_name;
	char *sub_charger_name;

	bool is_serial;
	bool aicl_disable;
	bool div_topoff_current;

	unsigned int sub_charger_condition;
	unsigned int sub_charger_condition_charge_power;
	int sub_charger_condition_current_max;
	int sub_charger_condition_fast_current;
	unsigned int *sub_charger_condition_online;
	unsigned int sub_charger_condition_online_size;

	int load_switch_control;
	unsigned int load_switch_condition_charge_power;
	unsigned int *load_switch_condition_online;
	unsigned int load_switch_condition_online_size;
	bool load_switch_always_on;
	bool jig_low_active;
	int jig_gpio;
};

struct sec_multi_charger_info {
	struct device *dev;
	struct sec_multi_charger_platform_data *pdata;
	struct power_supply		*psy_chg;

	int cable_type;
	int siop_level;
	int status;

	/* sub_charger should be disabled before 1st EOC */
	bool sub_is_charging;
	int multi_mode;

	unsigned int float_voltage;

	sec_charging_current_t total_current;
	sec_charging_current_t main_current;
	sec_charging_current_t sub_current;

	unsigned int full_check_current_1st;

	int chg_mode;
#if 0
	int cable_type;
	int status;
	bool is_charging;

	/* charging current : + charging, - OTG */
	int charging_current;
	unsigned charging_current_max;

	/* register programming */
	int reg_addr;
	int reg_data;
	int irq_base;
#endif
	bool is_jig_on;
};

#endif /* __SEC_MULTI_CHARGER_H */
