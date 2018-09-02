// https://leetcode.com/problems/combination-sum/description/
// 17.1 Count the number of score combinations

// I don't think I have used dynamic programming here 
class Solution {
public:

    vector<vector<int>> m_combs;
    vector<pair<int, int>> m_current;
    int m_target;
    
    void addToSet(int candidate, int count) {
        
        vector<int> candidates;
        for (size_t i = 0; i < m_current.size(); i++) {
            pair<int, int> p = m_current[i];
            for (size_t j = 0; j < p.second; j++) {
                candidates.push_back(p.first);
            }
        }
        
        m_combs.push_back(candidates);
    }
    
    void checkCombi(const vector<int>& candidates, size_t index, int currScore)
    {
        if (index >= candidates.size())
            return;
        
        int candi = candidates[index];
                
        int maxMultiple = (m_target - currScore) / candi; // E.g. 12 / 2 = 6
        
        for (int i = 0; i <= maxMultiple; i++) {
            int score = currScore + candi*i;
            
            m_current.push_back(make_pair(candi, i));

            if (score == m_target) {
                addToSet(candi, i);
            }
            else if (score < m_target) {
                checkCombi(candidates, index+1, score);
            }
            
            m_current.pop_back();
        }
    }
    
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        
        m_target = target;
        checkCombi(candidates, 0, 0);
        
        return m_combs;        
    }
};
