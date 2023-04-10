#pragma once


const UINT16 X2G_AC_CERTIFY_REQ			= 0x3100;
const UINT16 X2G_AC_CERTIFY_ACK			= 0x3101;
const UINT16 X2G_CH_LOAD_ALL_CHAR_REQ			= 0x3102;
const UINT16 X2G_CH_LOAD_ALL_CHAR_ACK			= 0x3103;
const UINT16 X2G_CH_LOAD_CHAR_ACK			= 0x3104;
const UINT16 X2G_CH_CREATE_CHAR_REQ			= 0x3105;
const UINT16 X2G_CH_CREATE_CHAR_ACK			= 0x3106;
const UINT16 X2G_CH_DELETE_CHAR_REQ			= 0x3107;
const UINT16 X2G_CH_DELETE_CHAR_ACK			= 0x3108;
const UINT16 X2G_CH_LOAD_ALL_SOLDIER_REQ			= 0x3109;
const UINT16 X2G_CH_LOAD_ALL_SOLDIER_ACK			= 0x310a;
const UINT16 X2G_CH_LOAD_SOLDIER_ACK			= 0x310b;
const UINT16 X2G_CH_CREATE_SOLDIER_ACK			= 0x310c;
const UINT16 X2G_CH_DELETE_SOLDIER_REQ			= 0x310d;
const UINT16 X2G_CH_DELETE_SOLDIER_ACK			= 0x310e;
const UINT16 X2G_CH_PAY_HIRED_SOLDIER_SALARY_NTF			= 0x310f;
const UINT16 X2G_CH_CHECK_NICK_DUPLICATE_REQ			= 0x3110;
const UINT16 X2G_CH_CHECK_NICK_DUPLICATE_ACK			= 0x3111;
const UINT16 X2G_CH_OBJECT_EXP_ACK			= 0x3112;
const UINT16 X2G_CH_LEVEL_UP_ACK			= 0x3113;
const UINT16 X2G_CH_LEVEL_UP_NTF			= 0x3114;
const UINT16 X2G_CH_MONEY_NTF			= 0x3115;
const UINT16 X2G_CH_SETUP_NO_RIVAL_NTF			= 0x3116;
const UINT16 X2G_CH_RELEASE_NO_RIVAL_NTF			= 0x3117;
const UINT16 X2G_CH_RESET_ABILITY_NTF			= 0x3118;
const UINT16 X2G_CH_COMPLETED_TUTORIAL_REQ			= 0x3119;
const UINT16 X2G_CH_COMPLETED_TUTORIAL_ACK			= 0x311a;
const UINT16 X2G_CH_CHAR_GAME_OPTION_REQ			= 0x311b;
const UINT16 X2G_CH_BATTLE_FORMATION_REQ			= 0x311c;
const UINT16 X2G_CH_BATTLE_FORMATION_ACK			= 0x311d;
const UINT16 X2G_WD_WORLD_ENTER_REQ			= 0x311e;
const UINT16 X2G_WD_USE_PORTAL_REQ			= 0x311f;
const UINT16 X2G_WD_WORLD_ENTER_ACK			= 0x3120;
const UINT16 X2G_WD_WORLD_CHANGE_FOR_QUEST_REQ			= 0x3121;
const UINT16 X2G_WD_WORLD_CHANGE_FOR_QUEST_ACK			= 0x3122;
const UINT16 X2G_WD_ENTER_OBJECT_NTF			= 0x3123;
const UINT16 X2G_WD_ALL_OBJECT_NTF			= 0x3124;
const UINT16 X2G_WD_WORLD_LEAVE_REQ			= 0x3125;
const UINT16 X2G_WD_LEAVE_OBJECT_NTF			= 0x3126;
const UINT16 X2G_WD_MOVE_REQ			= 0x3127;
const UINT16 X2G_WD_MOVE_ACK			= 0x3128;
const UINT16 X2G_WD_MOVE_NTF			= 0x3129;
const UINT16 X2G_WD_STOP_REQ			= 0x312a;
const UINT16 X2G_WD_STOP_NTF			= 0x312b;
const UINT16 X2G_WD_MOTION_REQ			= 0x312c;
const UINT16 X2G_WD_MOTION_ACK			= 0x312d;
const UINT16 X2G_WD_MOTION_NTF			= 0x312e;
const UINT16 X2G_WD_WORLD_PUZZLE_REQ			= 0x312f;
const UINT16 X2G_WD_WORLD_PUZZLE_NTF			= 0x3130;
const UINT16 X2G_WD_WORLD_MAP_OPEN_REQ			= 0x3131;
const UINT16 X2G_WD_WORLD_MAP_OPEN_ACK			= 0x3132;
const UINT16 X2G_BD_CHAT_REQ			= 0x3133;
const UINT16 X2G_BD_TARGET_CHAT_REQ			= 0x3134;
const UINT16 X2G_BD_CHAT_ACK			= 0x3135;
const UINT16 X2G_BD_CHAT_NTF			= 0x3136;
const UINT16 X2G_BD_NOTICE_CHAT_NTF			= 0x3137;
const UINT16 X2G_OB_REGEN_NTF			= 0x3138;
const UINT16 X2G_OB_DEATH_NTF			= 0x3139;
const UINT16 X2G_OB_REVIVAL_NTF			= 0x313a;
const UINT16 X2G_SK_LOAD_CHAR_SKILL_ACK			= 0x313b;
const UINT16 X2G_SK_SKILL_LEARN_REQ			= 0x313c;
const UINT16 X2G_SK_SKILL_LEARN_ACK			= 0x313d;
const UINT16 X2G_SK_SKILL_LEARN_NTF			= 0x313e;
const UINT16 X2G_SK_SKILL_LEVELUP_REQ			= 0x313f;
const UINT16 X2G_SK_SKILL_LEVELUP_ACK			= 0x3140;
const UINT16 X2G_SK_SKILL_LEVELUP_NTF			= 0x3141;
const UINT16 X2G_SK_SKILL_QUICK_SLOT_REQ			= 0x3142;
const UINT16 X2G_SK_SKILL_QUICK_SLOT_ACK			= 0x3143;
const UINT16 X2G_SK_ATTACK_REQ			= 0x3144;
const UINT16 X2G_SK_ATTACK_ACK			= 0x3145;
const UINT16 X2G_SK_ATTACK_NTF			= 0x3146;
const UINT16 X2G_SK_INSERT_BUFF_NTF			= 0x3147;
const UINT16 X2G_SK_DELETE_BUFF_NTF			= 0x3148;
const UINT16 X2G_SK_HEAL_NTF			= 0x3149;
const UINT16 X2G_BF_BATTLE_OPEN_REQ			= 0x314a;
const UINT16 X2G_BF_BATTLE_OPEN_ACK			= 0x314b;
const UINT16 X2G_BF_BATTLE_INTRUDE_CHAR_REQ			= 0x314c;
const UINT16 X2G_BF_BATTLE_INTRUDE_CHAR_ACK			= 0x314d;
const UINT16 X2G_BF_BATTLE_INTRUDE_CHAR_NTF			= 0x314e;
const UINT16 X2G_BF_BATTLE_INTRUDE_MONSTER_REQ			= 0x314f;
const UINT16 X2G_BF_BATTLE_INTRUDE_MONSTER_ACK			= 0x3150;
const UINT16 X2G_BF_BATTLE_OBJECT_NTF			= 0x3151;
const UINT16 X2G_BF_BATTLE_ENTER_ACK			= 0x3152;
const UINT16 X2G_BF_ENTER_BATTLE_OBJECT_NTF			= 0x3153;
const UINT16 X2G_BF_ALL_BATTLE_OBJECT_NTF			= 0x3154;
const UINT16 X2G_BF_BATTLE_LEAVE_REQ			= 0x3155;
const UINT16 X2G_BF_BATTLE_LEAVE_ACK			= 0x3156;
const UINT16 X2G_BF_LEAVE_BATTLE_OBJECT_NTF			= 0x3157;
const UINT16 X2G_BF_BATTLE_MOVE_REQ			= 0x3158;
const UINT16 X2G_BF_BATTLE_MOVE_ACK			= 0x3159;
const UINT16 X2G_BF_BATTLE_MOVE_NTF			= 0x315a;
const UINT16 X2G_BF_BATTLE_STOP_NTF			= 0x315b;
const UINT16 X2G_BF_BATTLE_NEXT_STATUS_REQ			= 0x315c;
const UINT16 X2G_BF_BATTLE_NEXT_STATUS_ACK			= 0x315d;
const UINT16 X2G_BF_BATTLE_STATUS_NTF			= 0x315e;
const UINT16 X2G_BF_BATTLE_TURN_WAITING_NTF			= 0x315f;
const UINT16 X2G_BF_BATTLE_PVP_REQ			= 0x3160;
const UINT16 X2G_BF_BATTLE_PVP_ACK			= 0x3161;
const UINT16 X2G_BF_BATTLE_PVP_RESULT_REQ			= 0x3162;
const UINT16 X2G_BF_BATTLE_PVP_RESULT_ACK			= 0x3163;
const UINT16 X2G_BF_BATTLE_SKIP_ENTER_REQ			= 0x3164;
const UINT16 X2G_BF_BATTLE_SKIP_ENTER_ACK			= 0x3165;
const UINT16 X2G_BF_BATTLE_SKIP_LEAVE_REQ			= 0x3166;
const UINT16 X2G_BF_BATTLE_SKIP_LEAVE_ACK			= 0x3167;
const UINT16 X2G_BF_BATTLE_SKIP_SKILL_CASTING_REQ			= 0x3168;
const UINT16 X2G_BF_BATTLE_SKIP_SKILL_CASTING_ACK			= 0x3169;
const UINT16 X2G_BF_BATTLE_SKIP_SKILL_CASTING_NTF			= 0x316a;
const UINT16 X2G_BF_BATTLE_TOGGLE_SOLDIER_REQ			= 0x316b;
const UINT16 X2G_BF_BATTLE_TOGGLE_SOLDIER_ACK			= 0x316c;
const UINT16 X2G_BF_BATTLE_TOGGLE_SOLDIER_NTF			= 0x316d;
const UINT16 X2G_IT_LOAD_INVENTORY_ITEM_ACK			= 0x316e;
const UINT16 X2G_IT_QUICK_SLOT_REQ			= 0x316f;
const UINT16 X2G_IT_QUICK_SLOT_ACK			= 0x3170;
const UINT16 X2G_IT_BUY_ITEM_REQ			= 0x3171;
const UINT16 X2G_IT_BUY_ITEM_ACK			= 0x3172;
const UINT16 X2G_IT_SELL_ITEM_REQ			= 0x3173;
const UINT16 X2G_IT_SELL_ITEM_ACK			= 0x3174;
const UINT16 X2G_IT_PICKUP_ITEM_ACK			= 0x3175;
const UINT16 X2G_IT_PICKUP_ITEM_NTF			= 0x3176;
const UINT16 X2G_IT_DESTROY_ITEM_REQ			= 0x3177;
const UINT16 X2G_IT_DESTROY_ITEM_ACK			= 0x3178;
const UINT16 X2G_IT_INVENTORY_CHANGE_REQ			= 0x3179;
const UINT16 X2G_IT_INVENTORY_CHANGE_ACK			= 0x317a;
const UINT16 X2G_IT_EQUIP_CHANGE_REQ			= 0x317b;
const UINT16 X2G_IT_EQUIP_CHANGE_ACK			= 0x317c;
const UINT16 X2G_IT_EQUIP_CHANGE_NTF			= 0x317d;
const UINT16 X2G_IT_GIFT_REQ			= 0x317e;
const UINT16 X2G_IT_GIFT_ACK			= 0x317f;
const UINT16 X2G_IT_GIFT_EQUIP_CHANGE_REQ			= 0x3180;
const UINT16 X2G_IT_GIFT_EQUIP_CHANGE_ACK			= 0x3181;
const UINT16 X2G_IT_GIFT_EQUIP_CHANGE_NTF			= 0x3182;
const UINT16 X2G_IT_USE_ITEM_REQ			= 0x3183;
const UINT16 X2G_IT_USE_ITEM_ON_BATTLE_REQ			= 0x3184;
const UINT16 X2G_IT_USE_ITEM_ACK			= 0x3185;
const UINT16 X2G_IT_USE_ITEM_NTF			= 0x3186;
const UINT16 X2G_IT_UPDATE_ITEM_NTF			= 0x3187;
const UINT16 X2G_IT_SPLITE_ITEM_REQ			= 0x3188;
const UINT16 X2G_IT_SPLITE_ITEM_ACK			= 0x3189;
const UINT16 X2G_IT_COMBINE_ITEM_REQ			= 0x318a;
const UINT16 X2G_IT_COMBINE_ITEM_ACK			= 0x318b;
const UINT16 X2G_QT_CHAR_QUEST_LIST_REQ			= 0x318c;
const UINT16 X2G_QT_CHAR_QUEST_LIST_ACK			= 0x318d;
const UINT16 X2G_QT_CHAR_QUEST_INSERT_REQ			= 0x318e;
const UINT16 X2G_QT_CHAR_QUEST_INSERT_ACK			= 0x318f;
const UINT16 X2G_QT_CHAR_HELLO_NPC_REQ			= 0x3190;
const UINT16 X2G_QT_CHAR_HELLO_NPC_ACK			= 0x3191;
const UINT16 X2G_QT_CHAR_GOODBYE_NPC_REQ			= 0x3192;
const UINT16 X2G_QT_CHAR_QUEST_TALK_NPC_REQ			= 0x3193;
const UINT16 X2G_QT_CHAR_QUEST_TALK_NPC_ACK			= 0x3194;
const UINT16 X2G_QT_CHAR_QUEST_UPDATE_ACK			= 0x3195;
const UINT16 X2G_QT_CHAR_QUEST_PROGRESS_UPDATE_ACK			= 0x3196;
const UINT16 X2G_QT_CHAR_QUEST_REWARD_REQ			= 0x3197;
const UINT16 X2G_QT_CHAR_QUEST_REWARD_ACK			= 0x3198;
const UINT16 X2G_QT_CHAR_QUEST_DELETE_REQ			= 0x3199;
const UINT16 X2G_QT_CHAR_QUEST_DELETE_ACK			= 0x319a;
const UINT16 X2G_ML_MAIL_LIST_REQ			= 0x319b;
const UINT16 X2G_ML_MAIL_LIST_ACK			= 0x319c;
const UINT16 X2G_ML_SEND_MAIL_REQ			= 0x319d;
const UINT16 X2G_ML_SEND_MAIL_ACK			= 0x319e;
const UINT16 X2G_ML_RECIEVE_MAIL_NTF			= 0x319f;
const UINT16 X2G_ML_CHANGE_MAIL_STATUS_REQ			= 0x31a0;
const UINT16 X2G_ML_CHANGE_MAIL_STATUS_ACK			= 0x31a1;
const UINT16 X2G_ML_TAKE_MAIL_ITEM_NTF			= 0x31a2;
const UINT16 X2G_PT_CREATE_PARTY_REQ			= 0x31a3;
const UINT16 X2G_PT_CREATE_PARTY_ACK			= 0x31a4;
const UINT16 X2G_PT_CREATE_PARTY_NTF			= 0x31a5;
const UINT16 X2G_PT_CREATE_PARTY_ACCEPT_REQ			= 0x31a6;
const UINT16 X2G_PT_ENTER_PARTY_MEMBER_NTF			= 0x31a7;
const UINT16 X2G_PT_ALL_PARTY_MEMBER_NTF			= 0x31a8;
const UINT16 X2G_PT_LEAVE_PARTY_MEMBER_NTF			= 0x31a9;
const UINT16 X2G_PT_DELETE_PARTY_REQ			= 0x31aa;
const UINT16 X2G_PT_DELETE_PARTY_ACK			= 0x31ab;
const UINT16 X2G_PT_DELETE_PARTY_NTF			= 0x31ac;
const UINT16 X2G_PT_INVITE_PARTY_REQ			= 0x31ad;
const UINT16 X2G_PT_INVITE_PARTY_ACK			= 0x31ae;
const UINT16 X2G_PT_INVITE_PARTY_NTF			= 0x31af;
const UINT16 X2G_PT_INVITE_PARTY_ACCEPT_REQ			= 0x31b0;
const UINT16 X2G_PT_ENTER_PARTY_REQ			= 0x31b1;
const UINT16 X2G_PT_ENTER_PARTY_ACK			= 0x31b2;
const UINT16 X2G_PT_ENTER_PARTY_NTF			= 0x31b3;
const UINT16 X2G_PT_ENTER_PARTY_ACCEPT_REQ			= 0x31b4;
const UINT16 X2G_PT_LEAVE_PARTY_REQ			= 0x31b5;
const UINT16 X2G_PT_LEAVE_PARTY_ACK			= 0x31b6;
const UINT16 X2G_PT_LEAVE_PARTY_NTF			= 0x31b7;
const UINT16 X2G_PT_BANISH_PARTY_MEMBER_REQ			= 0x31b8;
const UINT16 X2G_PT_BANISH_PARTY_MEMBER_ACK			= 0x31b9;
const UINT16 X2G_PT_BANISH_PARTY_MEMBER_NTF			= 0x31ba;
const UINT16 X2G_PT_CHANGE_MASTER_REQ			= 0x31bb;
const UINT16 X2G_PT_CHANGE_MASTER_ACK			= 0x31bc;
const UINT16 X2G_PT_CHANGE_MASTER_NTF			= 0x31bd;
const UINT16 X2G_PT_ONLINE_PARTY_NTF			= 0x31be;
const UINT16 X2G_PT_OFFLINE_PARTY_NTF			= 0x31bf;
const UINT16 X2G_PT_CHANGE_DISTRIBUTE_REQ			= 0x31c0;
const UINT16 X2G_PT_CHANGE_DISTRIBUTE_ACK			= 0x31c1;
const UINT16 X2G_PT_CHANGE_DISTRIBUTE_NTF			= 0x31c2;
const UINT16 X2G_PT_PARTY_MEMBER_MOVE_NTF			= 0x31c3;
const UINT16 X2G_PT_PARTY_MEMBER_REGEN_NTF			= 0x31c4;
const UINT16 X2G_PT_PARTY_MEMBER_DAMAGE_NTF			= 0x31c5;
const UINT16 X2G_PT_PARTY_MEMBER_REVIVAL_NTF			= 0x31c6;
const UINT16 X2G_PT_PARTY_MEMBER_DEAD_NTF			= 0x31c7;
const UINT16 X2G_TD_TRADE_REQ			= 0x31c8;
const UINT16 X2G_TD_TRADE_ACK			= 0x31c9;
const UINT16 X2G_TD_TRADE_NTF			= 0x31ca;
const UINT16 X2G_TD_TRADE_ENTER_REQ			= 0x31cb;
const UINT16 X2G_TD_TRADE_CANCEL_REQ			= 0x31cc;
const UINT16 X2G_TD_TRADE_CANCEL_NTF			= 0x31cd;
const UINT16 X2G_TD_TRADE_UPLOAD_MONEY_REQ			= 0x31ce;
const UINT16 X2G_TD_TRADE_UPLOAD_MONEY_ACK			= 0x31cf;
const UINT16 X2G_TD_TRADE_UPLOAD_MONEY_NTF			= 0x31d0;
const UINT16 X2G_TD_TRADE_UPLOAD_ITEM_REQ			= 0x31d1;
const UINT16 X2G_TD_TRADE_UPLOAD_ITEM_ACK			= 0x31d2;
const UINT16 X2G_TD_TRADE_UPLOAD_ITEM_NTF			= 0x31d3;
const UINT16 X2G_TD_TRADE_DOWNLOAD_ITEM_REQ			= 0x31d4;
const UINT16 X2G_TD_TRADE_DOWNLOAD_ITEM_ACK			= 0x31d5;
const UINT16 X2G_TD_TRADE_DOWNLOAD_ITEM_NTF			= 0x31d6;
const UINT16 X2G_TD_TRADE_CHAT_REQ			= 0x31d7;
const UINT16 X2G_TD_TRADE_CHAT_NTF			= 0x31d8;
const UINT16 X2G_TD_TRADE_ACCEPT_REQ			= 0x31d9;
const UINT16 X2G_TD_TRADE_ACCEPT_NTF			= 0x31da;
const UINT16 X2G_TD_TRADE_COMPLETE_REQ			= 0x31db;
const UINT16 X2G_TD_TRADE_COMPLETE_ACK			= 0x31dc;
const UINT16 X2G_TD_TRADE_COMPLETE_NTF			= 0x31dd;
const UINT16 X2G_TD_TRADE_LIST_NTF			= 0x31de;
const UINT16 X2G_AU_AUCTION_LIST_REQ			= 0x31df;
const UINT16 X2G_AU_AUCTION_LIST_ACK			= 0x31e0;
const UINT16 X2G_AU_AUCTION_LIST_NTF			= 0x31e1;
const UINT16 X2G_AU_AUCTION_CREATE_REQ			= 0x31e2;
const UINT16 X2G_AU_AUCTION_CREATE_ACK			= 0x31e3;
const UINT16 X2G_AU_AUCTION_CREATE_NTF			= 0x31e4;
const UINT16 X2G_AU_AUCTION_TENDER_REQ			= 0x31e5;
const UINT16 X2G_AU_AUCTION_TENDER_ACK			= 0x31e6;
const UINT16 X2G_AU_AUCTION_TENDER_NTF			= 0x31e7;
const UINT16 X2G_AU_AUCTION_RETURN_REQ			= 0x31e8;
const UINT16 X2G_AU_AUCTION_RETURN_ACK			= 0x31e9;