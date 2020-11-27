/*************************************************

����Ϸ�ƶ�ʱ���������κθĶ�����ֱ�ӷ����κ�Ŀ¼�ڡ�

*************************************************/


/**********************************************************************
����Ʒ��ϸ˵����

_qxd_.c  ������ж���Ʒ������������Ϸ���˳���Ϸ����Ϸ��ָ�
                   ��Ϸ�����⼰���������Ѷ���ز�����
hj_wiztools.c      ��ʦ���ߣ������У��ɸ�����Ϸ������ȣ���ʱ��ӣ�


hj_box.c ���䣬��ʱ��������������Ʒ     ���Ϊ  "hj_game/obj","box"

hj_npc_kill.c  ɱ¾��NPC���౻��ΪЯ�����屦��֮NPCʹ��
               ���Ϊ "hj_game/npc","kill"
hj_npc_quest.c ������NPC���䲿��������Ҫ������Ϸ;����õ� _qxd_.c ֧��
               ���Ϊ "hj_game/npc","quest"
hj_npc_other.c ��������NPC���������ڼ��ܡ��ָ��������������HP��Ѱ����н�������
               ���Ϊ "hj_game/npc","other"

hj_obj_weapon.c   ��������Ʒ��������ʽ����ħ��ˮ���������ô�����
                  ���Ϊ "hj_game/obj","sword" �� "hj_game/obj","magic"
hj_obj_quest.c    ��Ἴ������Ʒ���ļ���������ʵ���塣��ѧ����Ϸ�ڼ��ܡ�
                  ���Ϊ "hj_game/obj","quest"
hj_obj_other.c    ��������Ʒ���ļ���������ʵ���塣���ಹ��HP����Ʒ��
                  ���Ϊ "hj_game/obj","other"
hj_obj_tools.c    ��Ϸ��������Ʒ�����綨��ˮ���ɻ�ý�Ϊ׼ȷ�ĵ�ǰ�����Ǻŵȡ�
                  ���Ϊ "hj_game/obj","tools"
hj_obj_gem.c      ������obj_list.h������Ʒ��Ϊ���Ѱ����ʱ�ĸ�������ʹ�á�
                  ���Ϊ "hj_game/obj","the_gem"
hj_obj_gem_qz.c   ͬ�ϣ���һ������ĸ���������


feng_npc.c yu_npc.c lei_npc.c dian_npc.c �� fyld_npc.h
       �ĸ����ȵ�NPC��Я�������ҪѰ��ı��������Ҫ֮��ɲ���
feng_obj.c yu_obj.c lei_obj.c dian_objc. �� fyld_obj.h
       �ĸ����ȵ�OBJ,����Ʒ��ͨ���ϸ������

���Ϲ��ȵ�NPC��OBJ���������ִ���ж������������������Ƿ��Իٵĺ�����


hj_npc_ashman.c    �����С���ˣ������������������Ҷ��µ�������
                   ���Ϊ "hj_game/npc","ashman"


��������Ʒ    ��������Ʒ   ����Ϸ��������Ʒ��
*************************************************************************/


// HJ_DIR �ڴ˶��塣

#include "get_hj_dir.h"

string *obj_list_all=({

    HJ_DIR + "npc_obj/hj_box",
    HJ_DIR + "npc_obj/hj_box",        // ����������ӡ�
    HJ_DIR + "npc_obj/hj_npc_kill",
    HJ_DIR + "npc_obj/hj_npc_kill",   // ɱ¾�͹���������ӡ�
    HJ_DIR + "npc_obj/hj_npc_quest",
    HJ_DIR + "npc_obj/hj_npc_quest",  // ������NPC�������ӡ�
    HJ_DIR + "npc_obj/hj_npc_other",
    HJ_DIR + "npc_obj/hj_obj_tools",
    HJ_DIR + "npc_obj/hj_obj_quest",
    HJ_DIR + "npc_obj/hj_obj_other",
    HJ_DIR + "npc_obj/hj_obj_weapon",
});

string *obj_list_obj=({
    HJ_DIR + "npc_obj/hj_obj_tools",
    HJ_DIR + "npc_obj/hj_obj_quest",
    HJ_DIR + "npc_obj/hj_obj_other",
    HJ_DIR + "npc_obj/hj_obj_other",   // ����HP���Ʒ���һ������ȡ�á�
    HJ_DIR + "npc_obj/hj_obj_weapon",
});

string *obj_list_npc=({
    HJ_DIR + "npc_obj/hj_npc_kill",
    HJ_DIR + "npc_obj/hj_npc_quest",
    HJ_DIR + "npc_obj/hj_npc_other",
});

// �����Ǹ������ȵı�����ɲ��֡�

string *obj_list_feng=({
    HJ_DIR + "npc_obj/feng_obj",
    HJ_DIR + "npc_obj/feng_npc",
});

string *obj_list_yu=({
    HJ_DIR + "npc_obj/yu_obj",
    HJ_DIR + "npc_obj/yu_npc",
});

string *obj_list_lei=({
    HJ_DIR + "npc_obj/lei_obj",
    HJ_DIR + "npc_obj/lei_npc",
});

string *obj_list_dian=({
    HJ_DIR + "npc_obj/dian_obj",
    HJ_DIR + "npc_obj/dian_npc",
});

