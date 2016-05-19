package androidopencc;

import android.util.Log;

import com.example.xiongwei.androidopencc.R;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;

/**
 * Created by xiongwei on 16/5/19.
 */
@SuppressWarnings("JniMissingFunction")
public class AndroidOpenCC {
    static {
        System.loadLibrary("OpenCC");
    }

    private static AndroidOpenCC instance = null;

    //設置包名，因為OpenCC需要載入本地資源必須獲得當前應用的包名，包名只能通過
    String filePath = "/data/data/" + OpenCCApplication.getContext().getPackageName();
    String OPENCC_RES_PATH = filePath + "/OpenCC/";


    //設置C代碼部分的OpenCC資源路徑
    protected native void setOpenCCResPath(String inputStr);

    private native String ConvertSimpleToTraditional(String inputStr);

    public native String ConvertSimpleTextToTraditional(String inputStr);

    public native String ConvertTradTextToSimplized(String inputStr);

    /*將一個字符串中所有簡體漢字轉換成全部對應整體漢字，并拼接成串*/
    public String ConverSimpleToCorrespondingTradChar(String inputChars)
    {
        StringBuffer output = new StringBuffer("");
        for (int c = 0;c < inputChars.length();c++)
        {
            String subString = inputChars.substring(c,c+1);
            String outputString = ConvertSimpleToTraditional(subString);
            if (outputString.length() != 0)
            {
                output.append(ConvertSimpleToTraditional(subString));
            }
            else
            {
                output.append(subString);
            }
            Log.i("output",output.toString());
        }
        return output.toString();
    }

    public AndroidOpenCC()
    {
        //设置OpenCC资源文件路径
        setOpenCCResPath("/data/data/" + OpenCCApplication.getContext().getPackageName() + "/OpenCC/");
        //将资源文件填写到OpenCC文件路径中
        SetOpenCCResource();
    }

    public static AndroidOpenCC getInstance()
    {
        if (instance == null)
        {
            instance = new AndroidOpenCC();
        }
        return instance;
    }


    //設置OpenCC調用的資源
    protected void SetOpenCCResource(){
        int[] config = new int[]{R.raw.hk2s, R.raw.s2hk, R.raw.s2t, R.raw.t2s, R.raw.s2tw, R.raw.s2twp, R.raw.tw2s, R.raw.tw2sp};
        String[] configName = new String[]{"hk2s", "s2hk", "s2t", "t2s", "s2tw", "s2twp", "tw2s", "tw2sp"};

        int[] dictionary = new int[]{R.raw.hkvariants, R.raw.hkvariantsphrases, R.raw.hkvariantsrevphrases, R.raw.jpvariants, R.raw.stcharacters, R.raw.stphrases, R.raw.tscharacters, R.raw.tsphrases, R.raw.twphrasesit, R.raw.twphrasesname, R.raw.twphrasesother, R.raw.twvariants, R.raw.twvariantsrevphrases};
        String[] dictionaryName = new String[]{"HKVariants", "HKVariantsPhrases", "HKVariantsRevPhrases", "JPVariants", "STCharacters", "STPhrases", "TSCharacters", "TSPhrases", "TWPhrasesit", "TWPhrasesName", "TWPhrasesOther", "TWVariants", "TWVariantsRevPhrases"};

        int[] scheme = new int[]{R.raw.st_multi, R.raw.ts_multi, R.raw.variant};

        String[] schemeName = new String[]{"st_multi", "ts_multi", "variant"};

        int[] scripts = new int[]{R.raw.common, R.raw.find_target, R.raw.merge, R.raw.reverse, R.raw.sort_all, R.raw.sort, R.raw.common};
        String[] scriptsName = new String[]{"common", "find_target", "merge", "reverse", "sort_all", "sort", "common"};

        File OpenCC__dir = new File(OPENCC_RES_PATH);
        if (!OpenCC__dir.exists())
            OpenCC__dir.mkdir();

        setOpenCCResPath(OPENCC_RES_PATH);

        File lastResFile = new File(OPENCC_RES_PATH + "variant.txt");

        if (lastResFile.exists())
        {
            return;
        }

        //复制资源文件到本应用的文件夹
        for (int ct = 0; ct < config.length; ct++) {
            String fileName = configName[ct] + ".json";
            WriteFromRawToOpenCCPath(fileName,config[ct]);
        }

        for (int ct = 0; ct < scripts.length; ct++) {
            String fileName = scriptsName[ct] + ".py";
            WriteFromRawToOpenCCPath(fileName,scripts[ct]);
        }

        for (int ct = 0; ct < dictionary.length; ct++) {
            String fileName = dictionaryName[ct] + ".txt";
            WriteFromRawToOpenCCPath(fileName,dictionary[ct]);
        }

        for (int ct = 0; ct < scheme.length; ct++) {
            String fileName = schemeName[ct] + ".txt";
            WriteFromRawToOpenCCPath(fileName,scheme[ct]);
        }

    }

    private void WriteFromRawToOpenCCPath(String fileName,int rawId)
    {
        try {
            InputStream is = OpenCCApplication.getContext().getResources().openRawResource(
                    rawId);
            Log.i("复制资源文件", fileName);
            FileOutputStream fos = new FileOutputStream(OPENCC_RES_PATH + fileName);
            Log.i("复制资源文件", OPENCC_RES_PATH + fileName);
            byte[] buffer = new byte[8192];
            int count = 0;
            while ((count = is.read(buffer)) > 0) {
                fos.write(buffer, 0, count);
            }
            fos.close();
            is.close();
        }
        catch (Exception e) {

        }
    }
}
