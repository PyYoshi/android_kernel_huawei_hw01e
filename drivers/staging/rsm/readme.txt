==update:2011.08.04=============================================================================================================
��֧���ֹ����ش˼�⹦�ܡ�
1.����rsm��������±����������̣����ɵ�rsm.ko��busybox��load_rsm.sh�ڴ��system.imgʱ���Զ��ŵ�/system/binĿ¼�С�
2.��adb shell�����ֻ�����ʹ��load_rsm.sh�ű�����rsm.koģ�飬�������rsmĬ�ϻ�����н��̽��м�أ�Ĭ�ϼ��ʱ����Ϊ120s��
3.����ģ�����/proc/rsm/Ŀ¼������pname��timeout�����ļ���ʹ�������������в��������ã�
echo xx > pname ���ò���Ҫ��صĽ�������
echo xx > timeout ���ü�صļ��ʱ��
�������ų���صĽ�����Ϊ16����
���粻��Ҫ���rpcrotuer_smd_x��krmt_storagecln��krmt_storagecln��krtcclntd��krtcclntcbd��kbatteryclntd��kbatteryclntcbd�Ƚ��̣�������̼��ö��Ż��߿ո�����������ʱ����Ϊ60s��
echo rpcrotuer_smd_x��krmt_storagecln��krmt_storagecln��krtcclntd��krtcclntcbd��kbatteryclntd��kbatteryclntcbd > pname
echo 60 > timeout

==init:2011.07.13=============================================================================================================
1.��rsmĿ¼�µ�Դ����copy��kernel/drivers/staing/rsm/�£�ʹ�� make bootiamge����  ���ɵ�ko��out/target/product/msm7627_surf/obj/KERNEL_OBJ/drivers/staging/rsmĿ¼��

2.ʹ��load_rsm.sh�ű�����ģ��(ȷ���ֻ�����busybox���ű����õ�grep��sed)

3.����ģ�����/proc/rsm/Ŀ¼������pname��timeout�����ļ�
echo xx > pname ������Ҫ��صĽ�������
echo xx > timeout ���ü�صļ��ʱ��


˵����ʹ��rmmod ж��ģ��ʱ��Ҫ��timeoutʱ�䣬���������ʱ��δ����������汾�����������
