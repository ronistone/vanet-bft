from collections import Counter


def final_score(scores):
    count = Counter(scores)
    most_common = count.most_common(1)[0][0]
    return most_common


def consensus_fault_tolerant(score_dict):
    final_scores = {}
    for car, scores in score_dict.items():
        final_scores[car] = final_score(scores)
    return final_scores
