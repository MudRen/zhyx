// combine.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

mapping combine_list = ([

        // ����������
        ({ "/clone/fam/max/xuanhuang-1",
           "/clone/fam/max/longjia-1",
           "/clone/fam/item/kunlun-1",
           "/clone/fam/item/baxian-1", }) : "/clone/fam/max/zhenyu",

        // �������׵�
        ({ "/clone/fam/pill/dimai-1",
           "/clone/fam/pill/renshen4-1",
           "/clone/fam/etc/lv7d-1", }) : "/clone/fam/max/longjia",

        // �������䵤
        ({ "/clone/fam/pill/yulu-1",
           "/clone/fam/pill/lingzhi4-1",
           "/clone/fam/etc/lv7a-1", }) : "/clone/fam/max/xuanhuang",

        // ����ѪȪ
        ({ "/clone/fam/pill/puti2-1",
           "/clone/fam/pill/sheli3-1",
           "/clone/fam/etc/lv7b-1", }) : "/clone/fam/pill/dimai",

        // ������¶
        ({ "/clone/fam/pill/sheli2-1",
           "/clone/fam/pill/puti3-1",
           "/clone/fam/etc/lv7c-1", }) : "/clone/fam/pill/yulu",

        // ǧ����ĵ�
        ({ "/clone/fam/pill/renshen1-1",
           "/clone/fam/pill/renshen2-1",
           "/clone/fam/etc/lv5c-1", }) : "/clone/fam/pill/renshen4",

        // ǧ����֥��
        ({ "/clone/fam/pill/lingzhi1-1",
           "/clone/fam/pill/lingzhi2-1",
           "/clone/fam/etc/lv5c-1", }) : "/clone/fam/pill/lingzhi4",

        // ǧ��ѩ����
        ({ "/clone/fam/pill/xuelian1-1",
           "/clone/fam/pill/xuelian2-1",
           "/clone/fam/etc/lv5c-1", }) : "/clone/fam/pill/xuelian4",

        // ������ĵ�
        ({ "/clone/fam/pill/renshen1-1",
           "/clone/fam/etc/lv5e-1", }) : "/clone/fam/pill/renshen3",

        // ������֥��
        ({ "/clone/fam/pill/lingzhi1-1",
           "/clone/fam/etc/lv5e-1", }) : "/clone/fam/pill/lingzhi3",

        // ����ѩ����
        ({ "/clone/fam/pill/xuelian1-1",
           "/clone/fam/etc/lv5e-1", }) : "/clone/fam/pill/xuelian3",

        // ��쵤
        ({ "/clone/fam/pill/linghui1-1",
           "/clone/fam/pill/full1-1", }) : "/clone/fam/pill/linghui2",

        // ������
        ({ "/clone/fam/pill/neili1-1",
           "/clone/fam/pill/full1-1", }) : "/clone/fam/pill/neili2",

        // ������
        ({ "/clone/fam/pill/puti1-1",
           "/clone/fam/pill/puti2-1",
           "/clone/fam/pill/puti3-1", }) : "/clone/fam/pill/puti4",

        // ʥ����
        ({ "/clone/fam/pill/sheli1-1",
           "/clone/fam/pill/sheli2-1",
           "/clone/fam/pill/sheli3-1", }) : "/clone/fam/pill/sheli4",

        // ��������
        ({ "/clone/fam/pill/sheli2-1",
           "/clone/fam/pill/full1-1", }) : "/clone/fam/pill/sheli3",

        // ������
        ({ "/clone/fam/pill/puti2-1",
           "/clone/fam/pill/full1-1", }) : "/clone/fam/pill/puti3",

        // ������
        ({ "/clone/fam/pill/puti1-1",
           "/clone/fam/pill/full1-1", }) : "/clone/fam/pill/puti2",

        // ��������
        ({ "/clone/fam/pill/sheli1-1",
           "/clone/fam/pill/full1-1", }) : "/clone/fam/pill/sheli2",

        // ��������
        ({ "/clone/fam/etc/lv5a-1",
           "/clone/fam/etc/lv5b-1",
           "/clone/fam/etc/lv5d-1",
           "/clone/fam/etc/lv7d-1",
           "/clone/fam/gift/str3-1", }) : "/clone/fam/max/tianshu1",

        // ��������
        ({ "/clone/fam/etc/lv5a-1",
           "/clone/fam/etc/lv5b-1",
           "/clone/fam/etc/lv5d-1",
           "/clone/fam/etc/lv7d-1",
           "/clone/fam/gift/con3-1", }) : "/clone/fam/max/tianshu1",

        // ��������
        ({ "/clone/fam/etc/lv5a-1",
           "/clone/fam/etc/lv5b-1",
           "/clone/fam/etc/lv5d-1",
           "/clone/fam/etc/lv7d-1",
           "/clone/fam/gift/int3-1", }) : "/clone/fam/max/tianshu1",

        // ��������
        ({ "/clone/fam/etc/lv5a-1",
           "/clone/fam/etc/lv5b-1",
           "/clone/fam/etc/lv5d-1",
           "/clone/fam/etc/lv7d-1",
           "/clone/fam/gift/dex3-1", }) : "/clone/fam/max/tianshu1",

        // ���ž�������ͼ��Ƭƴ�ճ������ľ�������ͼ
        ({ "/clone/tattoo/spcs1-1",
           "/clone/tattoo/spcs1-2",
           "/clone/tattoo/spcs1-3",
           "/clone/tattoo/spcs1-4",
           "/clone/tattoo/spcs1-5" }) : "/clone/tattoo/spc1",

        // ���ŷ������ͼ��Ƭƴ�ճ������ķ������ͼ
        ({ "/clone/tattoo/spcs2-1",
           "/clone/tattoo/spcs2-2",
           "/clone/tattoo/spcs2-3",
           "/clone/tattoo/spcs2-4",
           "/clone/tattoo/spcs2-5" }) : "/clone/tattoo/spc2",

        // �������ʥͼ��Ƭƴ�ճ����������ʥͼ
        ({ "/clone/tattoo/spcs3-1",
           "/clone/tattoo/spcs3-2",
           "/clone/tattoo/spcs3-3",
           "/clone/tattoo/spcs3-4",
           "/clone/tattoo/spcs3-5" }) : "/clone/tattoo/spc3",

        // ���Űٹ�ҹ��ͼ��Ƭƴ�ճ������İٹ�ҹ��ͼ
        ({ "/clone/tattoo/spcs4-1",
           "/clone/tattoo/spcs4-2",
           "/clone/tattoo/spcs4-3",
           "/clone/tattoo/spcs4-4",
           "/clone/tattoo/spcs4-5" }) : "/clone/tattoo/spc4",

        // ������������ͼ��Ƭƴ�ճ���������������ͼ
        ({ "/clone/tattoo/spcs5-1",
           "/clone/tattoo/spcs5-2",
           "/clone/tattoo/spcs5-3",
           "/clone/tattoo/spcs5-4",
           "/clone/tattoo/spcs5-5" }) : "/clone/tattoo/spc5",

        // ����ǧ�ֹ���ͼ��Ƭƴ�ճ�������ǧ�ֹ���ͼ
        ({ "/clone/tattoo/spcs6-1",
           "/clone/tattoo/spcs6-2",
           "/clone/tattoo/spcs6-3",
           "/clone/tattoo/spcs6-4",
           "/clone/tattoo/spcs6-5" }) : "/clone/tattoo/spc6",

        // ���Ž���ɽ��ͼ��Ƭƴ�ճ������Ľ���ɽ��ͼ
        ({ "/clone/tattoo/spcs7-1",
           "/clone/tattoo/spcs7-2",
           "/clone/tattoo/spcs7-3",
           "/clone/tattoo/spcs7-4",
           "/clone/tattoo/spcs7-5" }) : "/clone/tattoo/spc7",

        // ���ź�������ͼ��Ƭƴ�ճ������ĺ�������ͼ
        ({ "/clone/tattoo/spcs8-1",
           "/clone/tattoo/spcs8-2",
           "/clone/tattoo/spcs8-3",
           "/clone/tattoo/spcs8-4",
           "/clone/tattoo/spcs8-5" }) : "/clone/tattoo/spc8",

        // ���ž�������ͼ��Ƭƴ�ճ������ľ�������ͼ
        ({ "/clone/tattoo/spcs9-1",
           "/clone/tattoo/spcs9-2",
           "/clone/tattoo/spcs9-3",
           "/clone/tattoo/spcs9-4",
           "/clone/tattoo/spcs9-5" }) : "/clone/tattoo/spc9",

        // ����ڤ������ͼ��Ƭƴ�ճ�������ڤ������ͼ
        ({ "/clone/tattoo/spcs10-1",
           "/clone/tattoo/spcs10-2",
           "/clone/tattoo/spcs10-3",
           "/clone/tattoo/spcs10-4",
           "/clone/tattoo/spcs10-5" }) : "/clone/tattoo/spc10",

        // ������ʯ��Ƭ�ϲ���Ϊһ����ʯ
        ({ "/clone/gift/cdiamond-1",
           "/clone/gift/cdiamond-2",
           "/clone/gift/cdiamond-3" }) : "/clone/gift/diamond",

        // ������ʯ�ϲ���Ϊһ��������ʯ
        ({ "/clone/gift/diamond-1",
           "/clone/gift/diamond-2",
           "/clone/gift/diamond-3" }) : "/clone/gift/fdiamond",

        // ����������ʯ�ϲ���Ϊһ����֮��ʯ
        ({ "/clone/gift/fdiamond-1",
           "/clone/gift/fdiamond-2",
           "/clone/gift/fdiamond-3" }) : "/clone/gift/mdiamond",

        // ���������Ƭ�ϲ���Ϊһ�����
        ({ "/clone/gift/cagate-1",
           "/clone/gift/cagate-2",
           "/clone/gift/cagate-3" }) : "/clone/gift/agate",

        // ������觺ϲ���Ϊһ���������
        ({ "/clone/gift/agate-1",
           "/clone/gift/agate-2",
           "/clone/gift/agate-3" }) : "/clone/gift/fagate",

        // ����������觺ϲ���Ϊһ����֮���
        ({ "/clone/gift/fagate-1",
           "/clone/gift/fagate-2",
           "/clone/gift/fagate-3" }) : "/clone/gift/magate",

        // ����ˮ����Ƭ�ϲ���Ϊһ��ˮ��
        ({ "/clone/gift/ccrystal-1",
           "/clone/gift/ccrystal-2",
           "/clone/gift/ccrystal-3" }) : "/clone/gift/crystal",

        // ����ˮ���ϲ���Ϊһ������ˮ��
        ({ "/clone/gift/crystal-1",
           "/clone/gift/crystal-2",
           "/clone/gift/crystal-3" }) : "/clone/gift/fcrystal",

        // ��������ˮ���ϲ���Ϊһ����֮ˮ��
        ({ "/clone/gift/fcrystal-1",
           "/clone/gift/fcrystal-2",
           "/clone/gift/fcrystal-3" }) : "/clone/gift/mcrystal",

        // ���������Ƭ�ϲ���Ϊһ�����
        ({ "/clone/gift/cjade-1",
           "/clone/gift/cjade-2",
           "/clone/gift/cjade-3" }) : "/clone/gift/jade",

        // �������ϲ���Ϊһ���������
        ({ "/clone/gift/jade-1",
           "/clone/gift/jade-2",
           "/clone/gift/jade-3" }) : "/clone/gift/fjade",

        // �����������ϲ���Ϊһ����֮���
        ({ "/clone/gift/fjade-1",
           "/clone/gift/fjade-2",
           "/clone/gift/fjade-3" }) : "/clone/gift/mjade",

        // Ǭ��ʥˮ
        ({ "/clone/fam/gift/int3-1",
           "/clone/fam/etc/lv7a-1",
           "/clone/fam/item/stone5-1" }) : "/clone/fam/item/bless_water",

        // Ǭ��ʥˮ
        ({ "/clone/fam/gift/con3-1",
           "/clone/fam/etc/lv7a-1",
           "/clone/fam/item/stone5-1" }) : "/clone/fam/item/bless_water",

        // Ǭ��ʥˮ
        ({ "/clone/fam/gift/dex3-1",
           "/clone/fam/etc/lv7a-1",
           "/clone/fam/item/stone5-1" }) : "/clone/fam/item/bless_water",

        // Ǭ��ʥˮ
        ({ "/clone/fam/gift/str3-1",
           "/clone/fam/etc/lv7a-1",
           "/clone/fam/item/stone5-1" }) : "/clone/fam/item/bless_water",

        // ��ʯ
        ({ "/clone/fam/item/stone3-1",
           "/clone/fam/item/stone1-1",
           }) : "/clone/fam/item/stone4",

        // �ʯ
        ({ "/clone/fam/item/stone2-1",
           "/clone/fam/item/stone1-1",
           }) : "/clone/fam/item/stone3",


        // ���»�ʯ
        ({ "/clone/fam/item/stone1-1",
           "/clone/fam/item/stone4-1",
           "/clone/fam/item/stone3-1",
           "/clone/fam/item/stone2-1",
           }) : "/clone/fam/item/stone5",


        /******************************************
                    ��Ƕ֮��Ʒ--�߼�
        *******************************************/
        // ���Ǳ���
       ({ "/clone/fam/etc/lv5f-1",
          "/clone/fam/etc/lv7c-1", // ������
          "/clone/fam/etc/lv7d-1", // ����ͨ����
          "/clone/fam/etc/lv7a-1", // ���������
          "/clone/fam/etc/prize5-1", // ���}Ѫ��
           }) : "/clone/fam/etc/bipo",

        // ��ʯ
       ({ "/clone/fam/item/baxian-1",
          "/clone/fam/item/kunlun-1",
          "/clone/fam/etc/lv7d-1",
          "/clone/fam/etc/lv7a-1",
          "/clone/fam/etc/prize5-1",
           }) : "/clone/fam/etc/huanshi",

        // ������
       ({ "/clone/fam/item/leihuo-1",
          "/clone/fam/item/lihuo-1",
          "/clone/fam/etc/lv5d-1", // �õ�����
          "/clone/fam/etc/lv7a-1",
          "/clone/fam/etc/prize5-1",
           }) : "/clone/fam/etc/binghuozhu",

        // ������
       ({ "/clone/fam/item/leihuo-1",
          "/clone/fam/etc/lv7c-1",
          "/clone/fam/etc/lv7d-1",
          "/clone/fam/etc/lv7a-1",
          "/clone/fam/etc/prize5-1",
           }) : "/clone/fam/etc/leishenzhu",

        /******************************************
                    ��Ƕ֮��Ʒ--��Ʒ
        *******************************************/
        // ��֮��������
       ({ "/clone/fam/etc/bipo-1",
          "/clone/fam/item/bless_water-1",
          "/clone/fam/etc/lv5d-1",
          "/clone/fam/etc/prize4-1",
           }) : "/clone/fam/etc/hanjing",

        // ħ֮�ġ�ħ
       ({ "/clone/fam/etc/huanshi-1",
          "/clone/fam/item/bless_water-1",
          "/clone/fam/etc/lv5d-1",
          "/clone/fam/item/stone5-1",
           }) : "/clone/fam/etc/mozhixin",

        // ��֮���顤��
       ({ "/clone/fam/etc/binghuozhu-1",
          "/clone/fam/item/bless_water-1",
          "/clone/fam/etc/lv7d-1",
          "/clone/fam/etc/lv7b-1",
           }) : "/clone/fam/etc/huojingling",

        // ����֮ͫ����
       ({ "/clone/fam/etc/leishenzhu-1",
          "/clone/fam/item/bless_water-1",
          "/clone/fam/etc/lv5d-1",
          "/clone/fam/item/zhenlong-1",
           }) : "/clone/fam/etc/leishentong",
      // �����޻���������һ�γԵ�ʧ��
       ({ "/clone/fam/gift/str3-1",
          "/clone/fam/gift/int3-1",
          "/clone/fam/gift/con3-1",
          "/clone/fam/gift/dex3-1",
          "/clone/fam/gift/str2-1",
          "/clone/fam/gift/int2-1",
          "/clone/fam/gift/con2-1",
          "/clone/fam/gift/dex2-1",
       }) : "/u/sanben/obj/fig",

     // �ĸ��ĳɵ���һ���߳ɵ��ϳ�һ��8.5�ɵ�(str)
       ({ "/clone/fam/gift/str1-1",  
          "/clone/fam/gift/int1-1",  
          "/clone/fam/gift/con1-1",  
          "/clone/fam/gift/dex1-1",  
          "/clone/fam/gift/str2-1",                  
        }) : "/clone/fam/gift/str3",

     // �ĸ��ĳɵ���һ���߳ɵ��ϳ�һ��8.5�ɵ�(int)
       ({ "/clone/fam/gift/str1-1",  
          "/clone/fam/gift/int1-1",  
          "/clone/fam/gift/con1-1",  
          "/clone/fam/gift/dex1-1",  
          "/clone/fam/gift/int2-1",                  
        }) : "/clone/fam/gift/int3",

     // �ĸ��ĳɵ���һ���߳ɵ��ϳ�һ��8.5�ɵ�(con)
       ({ "/clone/fam/gift/str1-1",  
          "/clone/fam/gift/int1-1",  
          "/clone/fam/gift/con1-1",  
          "/clone/fam/gift/dex1-1",
          "/clone/fam/gift/con2-1",                  
        }) : "/clone/fam/gift/con3",

     // �ĸ��ĳɵ���һ���߳ɵ��ϳ�һ��8.5�ɵ�(dex)
       ({ "/clone/fam/gift/str1-1",  
          "/clone/fam/gift/int1-1",  
          "/clone/fam/gift/con1-1",  
          "/clone/fam/gift/dex1-1", 
          "/clone/fam/gift/dex2-1",                  
        }) : "/clone/fam/gift/dex3",

    // ħ�� 
       ({ "/d/zhuanshi/obj/qilin-1", 
          "/d/zhuanshi/obj/shi-1", 
          "/d/zhuanshi/obj/jiushi-1", 
          "/d/zhuanshi/obj/quan-1", 
       }) : "/d/zhuanshi/obj/mojie", 

/********************************************************** 
 ����װ��������Ʒ���ǳ����ֻ��ͨ��һЩ����;����ȡ��ϳ�
 ������µȡ�
**********************************************************/
       // �����}��
       ({
          "/clone/fam/etc/longlin-1",
          "/clone/fam/etc/longlin-2",
          "/clone/fam/etc/longlin-3",
          "/clone/fam/etc/longlin-4",
          "/clone/fam/etc/longlin-5",
          "/clone/fam/etc/longlin-6",
          "/clone/fam/etc/longlin-7",
          "/clone/fam/etc/longlin-8",
          "/clone/fam/etc/longlin-9",
          "/clone/fam/etc/longlin-10",
          "/clone/fam/etc/longjiao-1",
          "/clone/fam/etc/longjiao-2",
          "/clone/fam/etc/longjin-1",
          "/clone/fam/etc/longxu-1",
          "/clone/fam/etc/longxu-2",
          "/clone/fam/etc/prize3-1",
          "/clone/fam/etc/prize3-2"}) : "/clone/fam/armor/yanlongjia",

       // ���޼�
       ({
          "/clone/fam/etc/jiaopige-1",
          "/clone/fam/etc/jiaopige-2",
          "/clone/fam/etc/jiaojin-1",
          "/clone/fam/etc/jiaoxu-1",
          "/clone/fam/etc/jiaoxu-2",
          "/clone/fam/pill/dimai-1",
          "/clone/fam/pill/dimai-2",
          "/clone/fam/pill/dimai-3",
          "/clone/fam/pill/dimai-4",
          "/clone/fam/pill/dimai-5",
          "/clone/fam/pill/dimai-6"}) : "/clone/fam/armor/zijiaojia",

      // ����Ƥ��
      ({
          "/clone/fam/etc/jiaopi-1",
          "/clone/fam/etc/jiaopi-2",
          "/clone/fam/etc/jiaopi-3",
          "/clone/fam/etc/jiaopi-4",
          "/clone/fam/etc/jiaopi-5",
          "/clone/fam/etc/jiaopi-6",
          "/clone/fam/etc/jiaopi-7",
          "/clone/fam/etc/jiaopi-8",
          "/clone/fam/etc/jiaopi-9",
          "/clone/fam/etc/jiaopi-10"}) : "/clone/fam/etc/jiaopige",

      //�����ë
      ({
          "/clone/fam/etc/yumao-1",
          "/clone/fam/etc/yumao-2",
          "/clone/fam/etc/yumao-3",
          "/clone/fam/etc/yumao-4",
          "/clone/fam/etc/yumao-5" }) : "/clone/fam/etc/yumao2",

       
       // �������
       ({
          "/clone/fam/etc/yumao2-1",
          "/clone/fam/etc/yumao2-2",
          "/clone/fam/etc/yumao2-3",
          "/clone/fam/etc/yumao2-4",
          "/clone/fam/etc/zhuquejiao-1",
          "/clone/fam/etc/zhuquejiao-2",
          "/clone/fam/etc/zhuquejin-1",
          "/clone/fam/etc/lv7a-1",
          "/clone/fam/etc/lv7a-2"}) : "/clone/fam/armor/fenghuangjia",

       // �׻�Ƥ��
      ({
          "/clone/fam/etc/hupi-1",
          "/clone/fam/etc/hupi-2",
          "/clone/fam/etc/hupi-3",
          "/clone/fam/etc/hupi-4",
          "/clone/fam/etc/hupi-5",
          "/clone/fam/etc/hupi-6",
          "/clone/fam/etc/hupi-7",
          "/clone/fam/etc/hupi-8",
          "/clone/fam/etc/hupi-9",
          "/clone/fam/etc/hupi-10"}) : "/clone/fam/etc/hupige",


       // ���ͷ��
      ({
          "/clone/fam/etc/yumao-1",
          "/clone/fam/etc/yumao-2",
          "/clone/fam/etc/fenghuangjiao-1",
          "/clone/fam/etc/fenghuangjiao-2",
          "/clone/fam/etc/fenghuangjiao-3",
          "/clone/fam/etc/fenghuangjiao-4"}) : "/clone/fam/armor/fenghuanghead",

       // �������
      ({
          "/clone/fam/etc/longlin-1",
          "/clone/fam/etc/longlin-2",
          "/clone/fam/etc/longjiao-1",
          "/clone/fam/etc/longjiao-2",
          "/clone/fam/etc/longjiao-3",
          "/clone/fam/etc/longjiao-4"}) : "/clone/fam/armor/yanlonghead",

       // ����ͷ­
      ({
          "/clone/fam/etc/jiaopi-1",
          "/clone/fam/etc/jiaopi-2",
          "/clone/fam/etc/jiaoxu-1",
          "/clone/fam/etc/jiaoxu-2",
          "/clone/fam/etc/jiaoxu-3",
          "/clone/fam/etc/jiaoxu-4"}) : "/clone/fam/armor/zijiaohead",

       // �׻�����
      ({
          "/clone/fam/etc/hugu-1",
          "/clone/fam/etc/hugu-2",
          "/clone/fam/etc/hupi-1",
          "/clone/fam/etc/hupi-2",
          "/clone/fam/etc/hupi-3",
          "/clone/fam/etc/hupi-4"}) : "/clone/fam/armor/baihuwrists",


       // �������
      ({
          "/clone/fam/etc/fenghuangjin-1",
          "/clone/fam/etc/fenghuangjin-2",
          "/clone/fam/etc/fenghuangjin-3",
          "/clone/fam/etc/fenghuangjin-4"}) : "/clone/fam/armor/fenghuangyaodai",

       // ������
      ({
          "/clone/fam/etc/hujin-1",
          "/clone/fam/etc/hujin-2",
          "/clone/fam/etc/hujin-3",
          "/clone/fam/etc/hujin-4"}) : "/clone/fam/armor/baihuyaodai",

       // ��ս��
      ({
          "/clone/fam/etc/hupige-1",
          "/clone/fam/etc/hupige-2",
          "/clone/fam/etc/hujin-1",
          "/clone/fam/etc/hugu-1",
          "/clone/fam/etc/hugu-2",
          "/clone/fam/etc/lv7d-1",
          "/clone/fam/etc/lv7d-2",
          "/clone/fam/etc/lv7d-3",
          "/clone/fam/etc/lv7d-4"}) : "/clone/fam/armor/shenhujia",

       // ��������
      ({
          "/clone/fam/etc/longjin-1",
          "/clone/fam/etc/longjin-2",
          "/clone/fam/etc/longjin-3",
          "/clone/fam/etc/longjin-4"}) : "/clone/fam/armor/yanlongyaodai",

       // ��������
      ({
          "/clone/fam/etc/jiaojin-1",
          "/clone/fam/etc/jiaojin-2",
          "/clone/fam/etc/jiaojin-3",
          "/clone/fam/etc/jiaojin-4"}) : "/clone/fam/armor/zijiaoyaodai",
       
]);

int main(object me, string arg)
{
        mapping same;                   // �ж��ظ�����Ʒ����Ҫ��mapping
	string *item_list, *name_list;  // �ϲ�����ƷID���ƥ��Ļ������ֱ�
        string bname;                   // ��Ʒ��Ӧ���ļ��Ļ�������
        object *ob_list;                // �ϲ���������Ʒ
        string *per;                    // mapping�м�¼�Ŀɺϲ��Ļ������ֱ�
	object obj;                     // ���ɵ���Ʒ
        int mp, i;

	if (! arg)
                return notify_fail("��Ҫ�ϲ�ʲô��Ʒ��\n");

        if (me->is_busy())
                return notify_fail("��æ����������������������ɣ�\n");

        if (me->is_fighting())
                return notify_fail("���������ڴ�ܣ�ûʱ������Щ���顣\n");

        if (me->query("max_jingli") < 300)
                return notify_fail("�����ڵľ�����Ϊ���ޣ��޷��ϳ���Ʒ��\n");

        if (me->query("jingli") < 300)
                return notify_fail("�����ھ������ã��޷��ϳ���Ʒ��\n");

        item_list = explode(arg, "&");
        ob_list   = allocate(sizeof(item_list));
        name_list = allocate(sizeof(item_list));
        same = allocate_mapping(sizeof(item_list));
        for (i = 0; i < sizeof(item_list); i++)
        {
                bname = item_list[i];
                while (bname[0] == ' ') bname = bname[1..<0];
                while (bname[strlen(bname) - 1] == ' ') bname = bname[0..<2];
                ob_list[i] = present(bname, me);

                if (! objectp(ob_list[i]))
                        return notify_fail("������û�� " + bname + " ������Ʒ����\n");

                if (i > 0 && member_array(ob_list[i], ob_list[0..i - 1]) != -1)
                        return notify_fail("�ϲ���Ʒ��Ҫָ����ͬ����Ʒ����Ҫ�ظ�ָ"
                                           "��һ����Ʒ��\n");

                bname = base_name(ob_list[i]);
                if (undefinedp(same[bname]))
                        same[bname] = 1;
                else
                        same[bname]++;
                name_list[i] = bname + "-" + (string) same[bname];
        }

        tell_object(me, HIW "\n��˫Ŀ΢�գ���������Ʒ�������У���ת�ھ���"
                        "ʹ���ǽ��ڡ�\n" NOR);

        me->start_busy(1);
        me->add("jingli", -200);
        foreach (per in keys(combine_list))
        {
                if (per - name_list == ({ }) && sizeof(per) == sizeof(name_list))
                {
                        // �ҵ��˺��ʵ����
                        obj = new(combine_list[per]);
                        for (i = 0; i < sizeof(ob_list); i++)
                        {
if (ob_list[i]->query_amount()){
                                        ob_list[i]->add_amount(-1);
                                    if (ob_list[i]->query_amount()==0)//by mike
                                        destruct(ob_list[i]);}
                                else
                                        destruct(ob_list[i]);
                        }
                        message("vision", HIW "\n��ʱ��ֻ��" + me->name() + HIW "����һ��"
                                          "�⻪��������ת˲���ţ��ƺ�������ʲô��ͬѰ����"
                                          "���顣\n\n" NOR, environment(me), ({me}));

                        tell_object(me, HIW "��ʱ��ֻ������⻪�����������㼱æ̯�����ƣ�"
                                        "��������\n��Ȼ������һ" + obj->query("unit") +
                                        obj->name() + HIW "����������ɫϼ�⡣\n\n" NOR);

			if (obj->query("value"))
			{
				mp = (int)(obj->query("value") / 700);
				mp = 1 + random(mp);
				if (mp < 1) mp = 1;
				if (mp > 100) mp = 100;

	                        me->add("magic_points", mp);
			        tell_object(me, HIC "��ͨ���ϳ�"+ obj->name() + HIC "����"
                                                "�����̣��Ӷ������" + chinese_number(mp) +
                                                "����ۡ�\n" NOR);
			}
                        me->add("max_jingli", -1);
                        obj->move(me, 1);
                        return 1;
                }
        }
        tell_object(me, HIR "���ǹ��˰��죬�ƺ�û���κα仯���㲻��һ��"
                        "��̾��\n" NOR);

        return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : combine <������Ʒ> & <������Ʒ> & ����

���ָ��������㽫ĳЩ������Ʒ�ϲ���һ���µ���Ʒ����Щ���ܺ�
�������Ҫ����ȥ�����ˡ�ÿ�κϲ�������ʧһ�㾫�������ޡ����
Ҫ�ϲ��ļ�����Ʒ������ͬ������Ҫָ�����ǵ���ţ�������������
ʯ�����Ҫ��һ������Ҫ���룺

  combine diamond & diamond 2 & diamond 3

HELP);
    	return 1;
}
