
inherit F_CLEAN_UP;
#include <ansi.h>

mapping places = ([
"wizard"        :         "herohall",
"baituo"        :         "map_bts",
"beijing"       :         "map_bj",
"changan"       :         "map_ca",
"city"          :         "map_yz",
"city3"         :         "map_cd",
"dali"          :         "map_dl",
"emei"          :         "map_em",
"foshan"        :         "map_fs",
"fuzhou"        :         "map_fz",
"guanwai"       :         "map_gw",
"gumu"          :         "map_gm",
"hangzhou"      :         "map_hz",
"heimuya"       :         "map_hmy",
"hengshan"      :         "map_ss",
"henshan"       :         "map_em",
"huanghe"       :         "map_ns",
"huashan"       :         "map_ws",
"jingzhou"      :         "map_jz",
"jueqing"       :         "map_jqg",
"village"       :         "map_hsc",
"kaifeng"       :         "map_kf",
"kunlun"        :         "map_kl",
"kunming"       :         "map_km",
"lingjiu"       :         "map_ljg",
"lingxiao"      :         "map_lxg",
"lingzhou"      :         "map_lz",
"luoyang"       :         "map_ly",
"meizhuang"     :         "map_mz",
"mingjiao"      :         "map_mj",
"motianya"      :         "map_mty",
"qingcheng"     :         "map_qc",
"quanzhen"      :         "map_zn",
"quanzhou"      :         "map_qz",
"shaolin"       :         "map_sl",
"songshan"      :         "map_cs",
"suzhou"        :         "map_sz",
"taishan"       :         "map_es",
"taohua"        :         "map_thd",
"tianlongsi"    :         "map_tls",
"tiezhang"      :         "map_tz",
"guiyun"        :         "map_gyz",
"wanjiegu"      :         "map_wjg",
"wudang"        :         "map_wd",
"wudu"          :         "map_wdj",
"xiangyang"     :         "map_xi",
"xiaoyao"       :         "map_xyl",
"xingxiu"       :         "map_xxh",
"xuanminggu"    :         "map_xmg",
"xuedao"        :         "map_xdm",
"yanziwu"       :         "map_yzw",
"zhongzhou"     :         "map_zz",
]);

int main(object me, string arg)
{
        string info, dir, tmp;
        string *list;
        object here;
        
        here = environment(me);
        if (sscanf(base_name(here), "/d/%s/%s", dir, tmp) != 2)
                 return notify_fail("�޵�ǰλ�õ���Ϣ��\n");

        tmp = filter_color(here->short());
        
        list = keys(places);        
        if (member_array(dir, list) == -1)
                  return notify_fail("�޵�ǰλ�õ���Ϣ��\n");

        info = read_file("/doc/help/" + places[dir]);
        info = color_filter(info);
        //info = filter_color(info);
        info = replace_string(info, tmp, NOR + HIR + BLINK + tmp + NOR);
        write(info + "\n");
        //write("dir == " + dir + "  tmp == " + tmp + "\n");
        //info = color_filter(read_file("/help/));

        return 1;
}
int help(object me)
{
        write(@HELP

���ָ�������ʾ�㵱ǰ����λ�á�

HELP
        );
        return 1;
}
