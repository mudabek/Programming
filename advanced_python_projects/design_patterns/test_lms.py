from lms import VideoItem, CompositeLearningItem, Quiz, ProgrammingAssignment


def test_composite_Works():
    # course == ??()
    # course.add(...)
    video_item_1 = VideoItem(name="Composite", length=20)
    video_item_2 = VideoItem(name="Composite v.2", length=10)
    lesson_composite = CompositeLearningItem(name="Composite lesson")
    lesson_composite.add(video_item_1)
    lesson_composite.add(video_item_2)
    assert (lesson_composite.estimate_study_time() == 45)

    video_item_3 = VideoItem(name="Adapters", length=20)
    quiz = Quiz(name="Quiz Adapters", questions=['a', 'b', 'c'])
    lesson_adapter = CompositeLearningItem(
        name="lesson adapter", learning_items=[video_item_3, quiz])
    assert (lesson_adapter.estimate_study_time() == 45)

    module_design_pattern = CompositeLearningItem(
        name="Design Patterns", learning_items=[lesson_composite, lesson_adapter])
    module_design_pattern.add(
        ProgrammingAssignment(name="Factory Prog Assignment", language="python")
    )
    assert (module_design_pattern.estimate_study_time() == 120 + 90)