import java.util.Random;

class RandomizedCollection {

    private static int M = 11;

    private Integer[] hashMap = new Integer[M];
    private int nums = 0;
    Random random;

    public RandomizedCollection() {
        random = new Random();
    }

    private void resize() {
        int newM;
        int topC = M / 2;
        if (nums >= topC) {
            newM = M * 2 + 1;
        } else if (topC > 9 && nums < topC / 2) {
            newM = M / 2 + 1;
        } else {
            return;
        }

        Integer[] newHashMap = new Integer[newM];
        for (int i = 0; i < M; i++) {
            if (hashMap[i] != null)
                insert(hashMap[i], newHashMap, newM);
        }
        hashMap = newHashMap;
        M = newM;
    }

    private boolean insert(int val, Integer[] hashMap, int M) {
        int i = (val % M + M) % M;
        boolean res = true;
        for (; hashMap[i] != null; i = (i + 1) % M) {
            if (hashMap[i] == val) {
                res = false;
            }
        }
        hashMap[i] = val;
        return res;
    }
    
    public boolean insert(int val) {
        boolean res = insert(val, hashMap, M);
        nums++;
        resize();
        return res;
    }
    
    public boolean remove(int val) {
        int i = (val % M + M) % M;
        for (;  hashMap[i] != null && hashMap[i] != val; i = (i + 1) % M) {

        }
        if (hashMap[i] == null) {
            return false;
        } else {
            hashMap[i] = null;
            nums--;
            int next = (i + 1) % M;
            while (hashMap[next] != null) {
                int v = hashMap[next];
                hashMap[next] = null;
                insert(v, hashMap, M);
                next = (next + 1) % M;
            }
            resize();
            return true;
        }
        
    }
    
    public int getRandom() {
        resize();
        int p = random.nextInt(M);
        while (hashMap[p] == null) {
            p = random.nextInt(M);
        }
        return hashMap[p];
    }

    public static void main(String[] args) {
        RandomizedCollection rc = new RandomizedCollection();
        rc.insert(1);
        rc.insert(0);
        rc.insert(1);
        rc.insert(1);
        rc.insert(1);
        rc.insert(1);
        rc.insert(1);
        rc.insert(1);
        rc.insert(0);
        rc.remove(0);
        rc.remove(0);

    }
}