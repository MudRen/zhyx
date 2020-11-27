#include <ansi.h>  
#include <weapon.h>
inherit CLUB;
mapping *weapon=({
([
  "name":           HIY"��ͭ��"NOR,
  "id":             "shutong gun",
  "long":           "����һ���þ�ͭ�������ͭ����\n",
  "value":          8000,
  "material":       "copper",
  "damage":         50,
  "wield_neili":    100,
  "wield_maxneili": 300,
  "wield_str":      18,
]),
([
  "name":           HIB"������"NOR,
  "id":             "duoming gun",
  "long":           "����һ���þ��ִ������������������ġ�\n",
  "value":          12000,
  "material":       "iron",
  "damage":         100,
  "wield_neili":    200,
  "wield_maxneili": 400,
  "wield_str":      20,
]),
([
  "name":           HIW"������"NOR,
  "id":             "liangyin gun",
  "long":           "����һ���ô����������ӵ�����������������ɷ�Ǻÿ���\n",
  "value":          30000,
  "material":       "silver",
  "damage":         150,
  "wield_neili":    400,
  "wield_maxneili": 600,
  "wield_str":      22,
]),
([
  "name":           HIY"�Ͻ��"NOR,
  "id":             "zijin gun",
  "long":       "����һ����Ұ��������ӵ��Ͻ������Ŀ���õĹ�â���Ի�����\n",
  "value":          50000,
  "material":       "gold",
  "damage":         200,
  "wield_neili":    400,
  "wield_maxneili": 800,
  "wield_str":      22,
]),
([
  "name":           BLK"������"NOR,
  "id":             "xuantie gun",
  "long":           "����һ���������������ӵ������������������쳣���ء�\n",
  "value":          80000,
  "material":       "crystal",
  "damage":         300,
  "wield_neili":    400,
  "wield_maxneili": 800,
  "wield_str":      23,
]),
([
  "name":           HIG"�����"NOR,
  "id":             "hanyu gun",
  "long":       "����һ����ǧ�꺮������ĺ��������ȡ�Ժ�����Ȼ��Ө����\n",
  "value":          80000,
  "material":       "crystal",
  "damage":         400,
  "wield_neili":    400,
  "wield_maxneili": 1000,
  "wield_str":      24,
]),
});

mapping zhuzao_level(object me)
{

        int skill,level,corn;
        object mine;      
 
        if(mine=present("tong kuang", me)) corn=0;
        else
           if(mine=present("tie kuang", me)) corn=1;
        else
           if(mine=present("ying kuang", me)) corn=2;
        else
           if(mine=present("jing kuang", me)) corn=3;
        else
           if(mine=present("xuantie kuang", me)) corn=4;
        else  
           if(mine=present("han tie", me)) corn=5;
        else corn=0;

        skill=me->query("work/zhuzhang")/100;

        if(skill>corn) level=corn;
           else level=skill;

        return weapon[level];
} 

void create()
{
        mapping prop;
        object me;
        me=this_player();

        prop=zhuzao_level(me);

        set_name(prop["name"], ({ prop["id"], "gun" }));
        init_club(prop["damage"]);  
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", prop["long"]);
                set("value", prop["value"]);   
                set("material", prop["material"]);
                set("wield_neili", prop["wield_neili"]);
                set("wield_maxneili", prop["wield_maxneili"]);
                set("wield_str", prop["wield_str"]);
                set("wield_msg", "$N��ৡ���һ���ͳ�һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n����������\n");
        }
        setup();
}
